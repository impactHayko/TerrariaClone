#include "Physics.h"

Physics::Physics()
{
	velocity = sf::Vector2f(0.f, 0.f);
	gravity = 980.0f;
	onGround = false;
}

Physics::~Physics()
{

}

void Physics::Update(float deltaTime)
{
	if (!onGround)
	{
		velocity.y += gravity * deltaTime;
	}
}

void Physics::setOnGround(bool grounded)
{
	this->onGround = grounded;
}

void Physics::setVelocity(float velY)
{
	this->velocity.y = velY;
}

bool Physics::isOnGround() const
{
	return onGround;
}

void Physics::jump(float jumpStrenght)
{
	this->velocity.y = -jumpStrenght;

	this->onGround = false;
}

sf::Vector2f Physics::getVelocity() const
{
	return velocity;
}