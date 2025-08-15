#pragma once
#include <SFML\Graphics.hpp>
#include "Collider.h"
//#include "Animation.h"

class Player : public sf::Drawable
{
public:
	sf::RectangleShape body;
	sf::Texture playerTexture;
	Player();
	~Player();

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		target.draw(body, states);
	}
	//Animation animation
};

