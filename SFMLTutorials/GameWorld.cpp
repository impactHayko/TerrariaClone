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

	//mView.setSize(sf::Vector2f(width, height));
	//mView.setCenter({ width / 2.0f, height / 2.0f });

	//Creating player and it's components
	mPlayer = new Player(&mPlayerTexture, sf::Vector2u (7,6) , .1f);
	mPlayerPhysics = &mPlayer->getPhysics();
	mPlayerCollider = new Collider(mPlayer->body);

	//Creating platform
	mPlatform.setSize(sf::Vector2f(width, 50.f));
	sf::Vector2f mPlatformSize = mPlatform.getSize();
	mPlatform.setOrigin({ mPlatformSize.x / 2, mPlatformSize.y / 2 });
	mPlatform.setPosition({ 300.f, 600.f });
	mPlatform.setFillColor(sf::Color::Green);
	mPlatformCollider = new Collider(mPlatform);

	//level (worldGrid)
	mWorldGrid = LoadWorldFromFile("level1.txt");

}

GameWorld::~GameWorld()
{
	delete mWindow;
	delete mPlayer;
	delete mPlayerCollider;
	delete mPlatformCollider;
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
		mPlayer->body.setScale(sf::Vector2f(-1.f, 1.f));
		mPlayer->animationUpdate(1, 0.02f);
		mPlayerPhysics->move(-200.0f);
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D))
	{
		mPlayer->body.setScale(sf::Vector2f(1.f, 1.f));
		mPlayer->animationUpdate(1, 0.02f);
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
	//player
	mPlayer->Update(deltaTime.asSeconds());
	CheckWorldCollision();

	//camera
	//mView.setCenter(mPlayer->body.getPosition());

	/*if (mPlayerCollider->CheckCollision(*mPlatformCollider, .0f))
	{
		if (mPlayerPhysics->getVelocity().y > 0)
		{
			mPlayerPhysics->setOnGround(true);
			mPlayerPhysics->setVelocity(0.f);
		}
	}*/
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

//void GameWorld::FindPlayerPosition()
//{
//	sf::FloatRect playerBounds = mPlayer->body.getGlobalBounds();
//	int leftTile = static_cast<int>(playerBounds.position.x / TILE_SIZE);
//	int rightTile = static_cast<int>((playerBounds.position.x + playerBounds.size.x) / TILE_SIZE);
//	int topTile = static_cast<int>(playerBounds.position.y / TILE_SIZE);
//	int bottomTile = static_cast<int>((playerBounds.position.y + playerBounds.size.y) / TILE_SIZE);
//
//	std::cout << "left tile : " << leftTile << std::endl;
//	std::cout << "right tile : " << rightTile << std::endl;
//	std::cout << "top tile : " << topTile << std::endl;
//	std::cout << "bottom tile : " << bottomTile << std::endl;
//}

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

void GameWorld::CheckWorldCollision()
{
	mPlayerPhysics->setOnGround(false);

	sf::FloatRect playerBounds = mPlayer->body.getGlobalBounds();
	int leftTile = static_cast<int>(playerBounds.position.x / TILE_SIZE);
	int rightTile = static_cast<int>((playerBounds.position.x + playerBounds.size.x) / TILE_SIZE);
	int topTile = static_cast<int>(playerBounds.position.y / TILE_SIZE);
	int bottomTile = static_cast<int>((playerBounds.position.y + playerBounds.size.y) / TILE_SIZE);

	for (int y = topTile; y <= bottomTile; ++y)
	{
		for (int x = leftTile; x <= rightTile; ++x)
		{
			if (y < 0 || y >= mWorldGrid.size() || x < 0 || x >= mWorldGrid[y].size())
			{
				continue;
			}

			int tileID = mWorldGrid[y][x];

			if (!isTileSolid(tileID))
			{
				continue;
			}

			sf::RectangleShape tileRect;
			tileRect.setSize({ TILE_SIZE, TILE_SIZE });
			tileRect.setOrigin({ TILE_SIZE / 2.0f, TILE_SIZE / 2.0f });
			tileRect.setPosition({x * TILE_SIZE + TILE_SIZE / 2.0f, y * TILE_SIZE + TILE_SIZE / 2.0f });

			Collider tileCollider(tileRect);

			if (mPlayerCollider->CheckCollision(tileCollider, 0.0f))
			{
				if (mPlayerPhysics->getVelocity().y > 0)
				{
					mPlayerPhysics->setOnGround(true);
					sf::Vector2f currentVelocity = mPlayerPhysics->getVelocity();
					currentVelocity.y = 0.f;
					mPlayerPhysics->setVelocity(currentVelocity.y);
				}
			}
		}
	}
}

//Render
void GameWorld::Render()
{
	mWindow->clear(sf::Color::Cyan);
	RenderWorld();
	//mWindow->setView(mView);
	//m_worldRenderer->draw(mView);
	mWindow->draw(*mPlayer);
	//mWindow->draw(mPlatform);
	mWindow->display();
	
}