#include "Player.h"
#include "Animation.h"

Player::Player()
	:body (sf::RectangleShape (sf::Vector2f(30.f, 60.f)))
{
	playerTexture.loadFromFile("Sprites/playersprite.png");

	body.setPosition({ 100.f, 300.f });
	body.setTexture(&playerTexture);
	body.setOrigin({ 15.f, 30.f });
	Animation animation(&playerTexture, sf::Vector2u(7, 6), 0.3f);
	
	//deltaTime
	float deltaTime = 0.0f;
	sf::Clock clock;
	animation.Update(1, deltaTime);
	body.setTextureRect(animation.uvRect);
}

Player::~Player()
{
	
}
