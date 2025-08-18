#include "Physics.h"

Physics::Physics()
{
	velocity = sf::Vector2f(0.f, 0.f);
	gravity = 980.0f;
}

Physics::~Physics()
{

}

void Physics::Update(float deltaTime)
{
	velocity.y += gravity * deltaTime;
}

sf::Vector2f Physics::getVelocity() const
{
	return velocity;
}