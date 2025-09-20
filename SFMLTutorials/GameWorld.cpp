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

	//Creating platform
	mPlatform.setSize(sf::Vector2f(width, 50.f));
	sf::Vector2f mPlatformSize = mPlatform.getSize();
	mPlatform.setOrigin({ mPlatformSize.x / 2, mPlatformSize.y / 2 });
	mPlatform.setPosition({ 300.f, 600.f });
	mPlatform.setFillColor(sf::Color::Green);
	mPlatformCollider = new Collider(mPlatform);
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

void GameWorld::GenerateChunk(int chunkX)
{
	Chunk newChunk;

	for (int col = 0; col < Chunk::CHUNK_WIDTH; ++col)
	{
		for (int cell = 0; cell < Chunk::CHUNK_HEIGHT; ++cell)
		{
			if (cell > 15)
			{
				newChunk.tiles[col][cell] = 1;
			}
			else
			{
				newChunk.tiles[col][cell] = 0;
			}
		}
	}
	mWorldChunks[chunkX] = newChunk;
	std::cout << "Generated chunk at X:" << chunkX << std::endl;
}

//Update nh00y
void GameWorld::Update(sf::Time deltaTime)
{
	//player
	mPlayerPhysics->setOnGround(false);
	mPlayer->Update(deltaTime.asSeconds());
	//CheckWorldCollision();

	//player position in which chunk
	int playerChunkX = static_cast<int>(floor(mPlayer->body.getPosition().x / (Chunk::CHUNK_WIDTH * TILE_SIZE)));

	for (int i = -1; i <= 1; ++i)
	{
		int chunkToCheck = playerChunkX + i;

		if (mWorldChunks.count(chunkToCheck) == 0)
		{
			GenerateChunk(chunkToCheck);
		}
	}

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
	mWindow->draw(*mPlayer);
	mWindow->draw(mPlatform);
	mWindow->display();
}