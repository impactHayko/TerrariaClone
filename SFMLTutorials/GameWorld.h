#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.h"
#include "PerlinNoise.h"

const float TILE_SIZE = 16.f;

class GameWorld
{
public:
	GameWorld();
	~GameWorld();

	void Run();

private:
	void ProcessEvents();
	void Update(sf::Time deltaTime);
	void Render();
	void RenderWorld();
	void GenerateWorld();
	void CheckWorldCollisionX();
	void CheckWorldCollisionY();
	bool isTileSolid(int tileID) const;

	sf::RenderWindow* mWindow;
	Player* mPlayer;
	Physics* mPlayerPhysics;
	sf::Texture mPlayerTexture;

	std::vector<std::vector<int>> mWorldGrid;
	PerlinNoise mPerlin;
};