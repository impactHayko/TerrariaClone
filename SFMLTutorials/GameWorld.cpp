#include "GameWorld.h"
#include <iostream>

GameWorld::GameWorld()
{
	mPlayerTexture.loadFromFile("Sprites/playersprite.png");

	//Creating window
	unsigned int width = 1280;
	unsigned int height = 720;
	mWindow = new sf::RenderWindow(sf::VideoMode({ width, height }), "Terraria Clone");
	mWindow->setFramerateLimit(60);

	//Creating player and it's components
	mPlayer = new Player(&mPlayerTexture, sf::Vector2u (7,6) , 0.3f);
	mPlayerPhysics = &mPlayer->getPhysics();
	mPlayerCollider = new Collider(mPlayer->body);

	////Creating platform
	//mPlatform.setSize(sf::Vector2f(withd, 50.f));
	//sf::Vector2f mPlatformSize = mPlatform.getSize();
	//mPlatform.setOrigin({ mPlatformSize.x / 2, mPlatformSize.y / 2 });
	//mPlatform.setPosition({ 300.f, 600.f });
	//mPlatform.setFillColor(sf::Color::Green);
	//mPlatformCollider = new Collider(mPlatform);

	//world generation
	mWorldGrid.resize(WORLD_WIDTH); // 100 coloumns
	for (int col = 0; col < WORLD_WIDTH; ++col)
	{
		mWorldGrid[col].resize(WORLD_HEIGHT);
		for (int cell = 0; cell < WORLD_HEIGHT; ++cell)
		{
			if (cell > 15)
			{
				mWorldGrid[col][cell] = 1; // 1 = earth
			}
			else
			{
				mWorldGrid[col][cell] = 0; // 0 = sky
			}
		}
	}
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

	/*if (mPlayerCollider->CheckCollision(*mPlatformCollider, .0f))
	{
		if (mPlayerPhysics->getVelocity().y > 0)
		{
			mPlayerPhysics->setOnGround(true);
			mPlayerPhysics->setVelocity(0.f);
		}
	}*/
}

//Render
void GameWorld::Render()
{
	mWindow->clear(sf::Color::Cyan);
	sf::RectangleShape tileShape({ TILE_SIZE, TILE_SIZE });

	for (int col = 0; col < WORLD_WIDTH; ++col)
	{
		for (int cell = 0; cell < WORLD_HEIGHT; ++cell)
		{
			if (mWorldGrid[col][cell] == 1)
			{
				float drawCol = col * TILE_SIZE;
				float drawCell = cell * TILE_SIZE;
				std::cout << "Trying to draw earth in: " << drawCol << "," << drawCell << std::endl;
				tileShape.setFillColor(sf::Color(150,75,0));
				tileShape.setPosition({ drawCol, drawCell });
				mWindow->draw(tileShape);
			}
		}
	}

	mWindow->draw(*mPlayer);
	//mWindow->draw(mPlatform);
	mWindow->display();
}