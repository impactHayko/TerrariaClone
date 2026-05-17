#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Player.h"
#include "GameWorld.h"

int main()
{
	//1. Creating theWorld
	GameWorld game;

	//2. Running
	game.Run();

	return 0;
}