#pragma once
#include <SFML/Graphics.hpp>

class Physics
{
public:
	Physics();
	void Update(float deltaTime);
	sf::Vector2f getVelocity() const;
	void setOnGround(bool grounded);
	void setVelocity(float velY);
	bool isOnGround() const;
	void jump(float jumpStrenght);
	~Physics();
private:
	sf::Vector2f velocity;
	float gravity;
	bool onGround;
};