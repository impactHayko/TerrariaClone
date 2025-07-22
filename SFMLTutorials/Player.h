#pragma once
#include <SFML\Graphics.hpp>
#include "Collider.h"
//#include "Animation.h"

class Player
{
public:
	Player();
	~Player();

private:
	sf::RectangleShape body;
	//Animation animation
};

