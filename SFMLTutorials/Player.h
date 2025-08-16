#pragma once
#include <SFML\Graphics.hpp>
#include "Animation.h"

class Player : public sf::Drawable
{
public:
	sf::RectangleShape body;
	sf::Texture playerTexture;

	Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
	void Update(float deltaTime);
	~Player();

private:
	Animation animation;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		target.draw(body, states);
	}	
};

