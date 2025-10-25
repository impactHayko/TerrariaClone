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
	void setVelocityX(float velX);
	bool isOnGround() const;
	void jump(float jumpStrenght);
	void move(float x);
	~Physics();
private:
	sf::Vector2f velocity;
	float gravity;
	bool onGround;
};