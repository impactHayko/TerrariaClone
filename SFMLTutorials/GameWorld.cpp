#include "GameWorld.h"
#include <iostream>
#include <fstream>
#include "WorldRenderer.h"
#include "parser.h"

GameWorld::GameWorld()
{
	mPlayerTexture.loadFromFile("Sprites/playersprite.png");

	//Creating window
	unsigned int width = 1280;
	unsigned int height = 720;
	mWindow = new sf::RenderWindow(sf::VideoMode({ width, height }), "Terraria Clone");
	mWindow->setFramerateLimit(60);

	//Creating player and it's components
	mPlayer = new Player(&mPlayerTexture, sf::Vector2u (7,6) , .1f);
	mPlayerPhysics = &mPlayer->getPhysics();

	//Creating platform
	mPlatform.setSize(sf::Vector2f(width, 50.f));
	sf::Vector2f mPlatformSize = mPlatform.getSize();
	mPlatform.setOrigin({ mPlatformSize.x / 2, mPlatformSize.y / 2 });
	mPlatform.setPosition({ 300.f, 600.f });
	mPlatform.setFillColor(sf::Color::Green);

	//level (worldGrid)
	mWorldGrid = LoadWorldFromFile("level1.txt");

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

	// Шаг 1: двигаем только по X, затем проверяем горизонтальные коллизии
	mPlayer->body.move({ vel.x * dt, 0.f });
	CheckWorldCollisionX();

	// Шаг 2: двигаем только по Y, затем проверяем вертикальные коллизии
	mPlayer->body.move({ 0.f, vel.y * dt });
	CheckWorldCollisionY();
}

//LevelRender
void GameWorld::RenderWorld()
{
	sf::RectangleShape tileShape({ TILE_SIZE, TILE_SIZE });

	for (int y = 0; y < mWorldGrid.size(); ++y)
	{
		for (int x = 0; x < mWorldGrid[y].size(); ++x)
		{
			int tileID = mWorldGrid[y][x];
			if (tileID != 0)
			{
				if (tileID == 1)
				{
					tileShape.setFillColor(sf::Color(150, 75, 0));
				}
				else if (tileID == 2)
				{
					tileShape.setFillColor(sf::Color(128, 128, 128));
				}

				tileShape.setPosition({ x * TILE_SIZE, y * TILE_SIZE });
				mWindow->draw(tileShape);
			}
		}
	}
}

bool GameWorld::isTileSolid(int tileID) const
{
	switch (tileID)
	{
		case 1:
		case 2:
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

			// Толкаем игрока горизонтально — в сторону, противоположную движению
			if (mPlayerPhysics->getVelocity().x > 0)
				mPlayer->body.move({ -intersection->size.x, 0.f });
			else
				mPlayer->body.move({  intersection->size.x, 0.f });

			mPlayerPhysics->setVelocityX(0.f);
			playerBounds = mPlayer->body.getGlobalBounds(); // обновляем после пуша
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
				// Падаем вниз — ставим на землю
				mPlayer->body.move({ 0.f, -intersection->size.y });
				mPlayerPhysics->setOnGround(true);
			}
			else
			{
				// Летим вверх — ударились о потолок
				mPlayer->body.move({ 0.f, intersection->size.y });
			}

			mPlayerPhysics->setVelocity(0.f);
			playerBounds = mPlayer->body.getGlobalBounds(); // обновляем после пуша
		}
	}
}

//Render
void GameWorld::Render()
{
	mWindow->clear(sf::Color::Cyan);
	RenderWorld();
	mWindow->draw(*mPlayer);
	mWindow->display();
	
}