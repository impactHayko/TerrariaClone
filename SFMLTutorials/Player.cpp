#include "Player.h"

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime)
	:body (sf::RectangleShape (sf::Vector2f(30.f, 60.f))),
	 animation(texture, imageCount, switchTime)
{
	body.setPosition({ 200.f, 300.f });
	body.setTexture(texture);
	body.setOrigin({ 15.f, 30.f });
}
void Player::Update(float deltaTime)
{
	physics.Update(deltaTime);
	body.setTextureRect(animation.uvRect);
}

void Player::animationUpdate(int row, float deltaTime, bool flipped)
{
	animation.Update(row, deltaTime, flipped);
}

Physics& Player::getPhysics()
{
	return physics;
}

Player::~Player()
{
	
}
