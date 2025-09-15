#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.h"
#include "Collider.h"
#include "Physics.h"

const int WORLD_WIDTH = 100;
const int WORLD_HEIGHT = 50;
const float TILE_SIZE = 40.f;

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
	std::vector<std::vector<int>> mWorldGrid;
};