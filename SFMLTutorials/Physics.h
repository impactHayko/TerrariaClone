#pragma once
#include <SFML/Graphics.hpp>

class Physics
{
public:
	Physics();
	void Update(float deltaTime);
	sf::Vector2f getVelocity() const;
	~Physics();
private:
	sf::Vector2f velocity;
	float gravity;
};