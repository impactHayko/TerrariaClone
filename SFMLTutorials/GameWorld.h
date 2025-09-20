#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include "Player.h"
#include "Collider.h"
#include "Physics.h"

const float TILE_SIZE = 40.f;

struct Chunk
{
	static const int CHUNK_WIDTH = 32;
	static const int CHUNK_HEIGHT = 50;

	std::vector<std::vector<int>> tiles;

	Chunk()
	{
		tiles.resize(CHUNK_WIDTH, std::vector<int>(CHUNK_HEIGHT, 0));
	}
};

class GameWorld
{
public:
	GameWorld();
	~GameWorld();

	void Run();

private:
	//Private methods for code to be organised
	void ProcessEvents();
	void Update(sf::Time deltaTime);
	void Render();
	//void CheckWorldCollision();
	void GenerateChunk(int chunkX);

	//Game Objects here instead of main
	sf::RenderWindow* mWindow;
	Player* mPlayer;
	Physics* mPlayerPhysics;
	Collider* mPlayerCollider;
	sf::Texture mPlayerTexture;

	//Platform
	sf::RectangleShape mPlatform;
	Collider* mPlatformCollider;

	//Tiles
	std::map<int, Chunk> mWorldChunks;
};