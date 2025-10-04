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
	mPlayer = new Player(&mPlayerTexture, sf::Vector2u (7,6) , 0.3f);
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
			mPlayerPhysics->jump(600.0f);
		}
	}


}

//Update nh00y
void GameWorld::Update(sf::Time deltaTime)
{
	//player
	mPlayerPhysics->setOnGround(false);
	mPlayer->Update(deltaTime.asSeconds());

	//camera
	//mView.setCenter(mPlayer->body.getPosition());

	if (mPlayerCollider->CheckCollision(*mPlatformCollider, .0f))
	{
		if (mPlayerPhysics->getVelocity().y > 0)
		{
			mPlayerPhysics->setOnGround(true);
			mPlayerPhysics->setVelocity(0.f);
		}
	}
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

//Render
void GameWorld::Render()
{
	mWindow->clear(sf::Color::Cyan);
	RenderWorld();
	//mWindow->setView(mView);
	//m_worldRenderer->draw(mView);
	mWindow->draw(*mPlayer);
	mWindow->draw(mPlatform);
	mWindow->display();
	
}