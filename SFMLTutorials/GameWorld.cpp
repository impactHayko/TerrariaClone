#include "GameWorld.h"
#include <algorithm>

GameWorld::GameWorld()
{
	mPlayerTexture.loadFromFile("Sprites/playersprite.png");

	//Creating window
	unsigned int width = 1920;
	unsigned int height = 1080;
	mWindow = new sf::RenderWindow(sf::VideoMode({ width, height }), "Terraria Clone");
	mWindow->setFramerateLimit(60);

	//Creating player and it's components
	mPlayer = new Player(&mPlayerTexture, sf::Vector2u (7,6) , .1f);
	mPlayerPhysics = &mPlayer->getPhysics();

	//level (worldGrid)
	//mWorldGrid = LoadWorldFromFile("level1.txt")
	mWorldGrid.resize(150, std::vector<int>(250, 0));
	GenerateWorld();

	//Spawn player on surface
	int spawnCol = 10;
	for (int y = 0; y < (int)mWorldGrid.size(); y++)
	{
		if (isTileSolid(mWorldGrid[y][spawnCol]))
		{
			float spawnX = spawnCol * TILE_SIZE + TILE_SIZE / 2.f;
			float spawnY = y * TILE_SIZE - 30.f;
			mPlayer->body.setPosition({ spawnX, spawnY });
			break;
		}
	}

}

GameWorld::~GameWorld()
{
	delete mWindow;
	delete mPlayer;
}

void GameWorld::Run()
{
	sf::Clock clock;
	while (mWindow->isOpen())
	{
		sf::Time deltaTime = clock.restart();
		ProcessEvents();
		Update(deltaTime);
		Render();
	}
}

//Processing Events
void GameWorld::ProcessEvents()
{
	while (const std::optional event = mWindow->pollEvent())
	{
		if (event->is<sf::Event::Closed>())
		{
			mWindow->close();
		}

		else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
		{
			if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
			{
				mWindow->close();
			}
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Space))
	{
		if (mPlayerPhysics->isOnGround())
		{
			mPlayerPhysics->jump(350.0f);
		}
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A))
	{
		mPlayer->animationUpdate(1, 0.02f, true);
		mPlayerPhysics->move(-200.0f);

	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D))
	{
		mPlayer->animationUpdate(1, 0.02f, false);
		mPlayerPhysics->move(200.0f);
	}

	else
	{
		mPlayerPhysics->setVelocityX(0.f);
	}


}

//Update nh00y
void GameWorld::Update(sf::Time deltaTime)
{
	float dt = deltaTime.asSeconds();
	mPlayer->Update(dt);

	sf::Vector2f vel = mPlayerPhysics->getVelocity();

	mPlayer->body.move({ vel.x * dt, 0.f });
	CheckWorldCollisionX();

	mPlayer->body.move({ 0.f, vel.y * dt });
	CheckWorldCollisionY();
}

void GameWorld::GenerateWorld()
{
	double scale = 18.0;
	int minSurface = 30;
	int maxSurface = 50;

	for (int x = 0; x < 250; x++)
	{
		double noise = mPerlin.noise2D(x / 250.0 * scale, 0);
		int surfaceY = static_cast<int>((noise + 1.0) / 2.0 * (maxSurface - minSurface) + minSurface);

		for (int y = 0; y < 150; y++)
		{
			if (y < surfaceY)
			{
				mWorldGrid[y][x] = 0;
			}
			else if (y == surfaceY)
			{
				mWorldGrid[y][x] = 3;
			}
			else
			{
				mWorldGrid[y][x] = 1;
			}
		}
	}
}

//LevelRender
void GameWorld::RenderWorld()
{
	sf::View view = mWindow->getView();
	sf::Vector2f center = view.getCenter();
	sf::Vector2f size = view.getSize();

	int startX = std::max(0, (int)((center.x - size.x / 2) / TILE_SIZE));
	int endX   = std::min((int)mWorldGrid[0].size() - 1, (int)((center.x + size.x / 2) / TILE_SIZE) + 1);
	int startY = std::max(0, (int)((center.y - size.y / 2) / TILE_SIZE));
	int endY   = std::min((int)mWorldGrid.size() - 1, (int)((center.y + size.y / 2) / TILE_SIZE) + 1);

	sf::VertexArray vertices(sf::PrimitiveType::Triangles);

	for (int y = startY; y <= endY; ++y)
	{
		for (int x = startX; x <= endX; ++x)
		{
			int tileID = mWorldGrid[y][x];
			if (tileID == 0) continue;

			sf::Color color;
			if      (tileID == 1) color = sf::Color(150, 75,  0);
			else if (tileID == 2) color = sf::Color(128, 128, 128);
			else if (tileID == 3) color = sf::Color(126, 200, 80);

			float px = x * TILE_SIZE;
			float py = y * TILE_SIZE;

			vertices.append(sf::Vertex{{ px,             py             }, color});
			vertices.append(sf::Vertex{{ px + TILE_SIZE, py             }, color});
			vertices.append(sf::Vertex{{ px,             py + TILE_SIZE }, color});

			vertices.append(sf::Vertex{{ px + TILE_SIZE, py             }, color});
			vertices.append(sf::Vertex{{ px + TILE_SIZE, py + TILE_SIZE }, color});
			vertices.append(sf::Vertex{{ px,             py + TILE_SIZE }, color});
		}
	}

	mWindow->draw(vertices);
}

bool GameWorld::isTileSolid(int tileID) const
{
	switch (tileID)
	{
		case 1: //dirt
		case 2: //stone
		case 3: //grass
			return true;

		default:
			return false;
	}
}

void GameWorld::CheckWorldCollisionX()
{
	sf::FloatRect playerBounds = mPlayer->body.getGlobalBounds();
	int leftTile   = static_cast<int>(playerBounds.position.x / TILE_SIZE);
	int rightTile  = static_cast<int>((playerBounds.position.x + playerBounds.size.x) / TILE_SIZE);
	int topTile    = static_cast<int>(playerBounds.position.y / TILE_SIZE);
	int bottomTile = static_cast<int>((playerBounds.position.y + playerBounds.size.y) / TILE_SIZE);

	for (int y = topTile; y <= bottomTile; ++y)
	{
		for (int x = leftTile; x <= rightTile; ++x)
		{
			if (y < 0 || y >= mWorldGrid.size() || x < 0 || x >= mWorldGrid[y].size())
				continue;
			if (!isTileSolid(mWorldGrid[y][x]))
				continue;

			sf::FloatRect tileBounds({ x * TILE_SIZE, y * TILE_SIZE }, { TILE_SIZE, TILE_SIZE });
			auto intersection = playerBounds.findIntersection(tileBounds);
			if (!intersection)
				continue;

			if (mPlayerPhysics->getVelocity().x > 0)
				mPlayer->body.move({ -intersection->size.x, 0.f });
			else
				mPlayer->body.move({  intersection->size.x, 0.f });

			mPlayerPhysics->setVelocityX(0.f);
			playerBounds = mPlayer->body.getGlobalBounds();
		}
	}
}

void GameWorld::CheckWorldCollisionY()
{
	mPlayerPhysics->setOnGround(false);

	sf::FloatRect playerBounds = mPlayer->body.getGlobalBounds();
	int leftTile   = static_cast<int>(playerBounds.position.x / TILE_SIZE);
	int rightTile  = static_cast<int>((playerBounds.position.x + playerBounds.size.x) / TILE_SIZE);
	int topTile    = static_cast<int>(playerBounds.position.y / TILE_SIZE);
	int bottomTile = static_cast<int>((playerBounds.position.y + playerBounds.size.y) / TILE_SIZE);

	for (int y = topTile; y <= bottomTile; ++y)
	{
		for (int x = leftTile; x <= rightTile; ++x)
		{
			if (y < 0 || y >= mWorldGrid.size() || x < 0 || x >= mWorldGrid[y].size())
				continue;
			if (!isTileSolid(mWorldGrid[y][x]))
				continue;

			sf::FloatRect tileBounds({ x * TILE_SIZE, y * TILE_SIZE }, { TILE_SIZE, TILE_SIZE });
			auto intersection = playerBounds.findIntersection(tileBounds);
			if (!intersection)
				continue;

			if (mPlayerPhysics->getVelocity().y > 0)
			{
				mPlayer->body.move({ 0.f, -intersection->size.y });
				mPlayerPhysics->setOnGround(true);
			}
			else
			{
				mPlayer->body.move({ 0.f, intersection->size.y });
			}

			mPlayerPhysics->setVelocity(0.f);
			playerBounds = mPlayer->body.getGlobalBounds();
		}
	}
}

//Render
void GameWorld::Render()
{
	sf::View view = mWindow->getDefaultView();
	sf::Vector2f playerPos = mPlayer->body.getPosition();

	float halfW = view.getSize().x / 2.f;
	float halfH = view.getSize().y / 2.f;
	float worldW = mWorldGrid[0].size() * TILE_SIZE;
	float worldH = mWorldGrid.size() * TILE_SIZE;

	float camX = std::clamp(playerPos.x, halfW, worldW - halfW);
	float camY = std::clamp(playerPos.y, halfH, worldH - halfH);
	view.setCenter({ camX, camY });
	mWindow->setView(view);

	mWindow->clear(sf::Color::Cyan);
	RenderWorld();
	mWindow->draw(*mPlayer);
	mWindow->display();
}