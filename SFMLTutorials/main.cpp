#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Collider.h"
#include "Animation.h"
#include "Player.h"
#include "GameWorld.h"

int main()
{
	//1. Creating theWorld
	GameWorld game;

	//2. Running
	game.Run();

	return 0;

	//unsigned int width = 800;
	//unsigned int height = 600;
	//sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode({ width,height }), "Tutorials"); //creating window with title "tutorials"
	//window->setFramerateLimit(60);
	//sf::Texture playerTexture;
	//playerTexture.loadFromFile("Sprites/playersprite.png");

	//std::vector<Collider> platformColliders;

	//Player saqo(&playerTexture, sf::Vector2u(7,6), 0.3f);

	////CREATING SQUARE
	//sf::RectangleShape square1({ 800.f, 60.f });
	//sf::Vector2f size = square1.getSize();
	//square1.setFillColor(sf::Color::Red);
	//square1.setOrigin({ size.x / 2, size.y / 2 });
	//square1.setPosition({ 400,450 });

	//Collider collider1(square1);
	//platformColliders.push_back(collider1);
	//
	//Collider saqoCollider(saqo.body);

	////deltaTime
	//float deltaTime = 0.0f;
	//sf::Clock clock;
	//
	//while (window->isOpen())
	//{
	//	saqo.getPhysics().setOnGround(false);
	//	deltaTime = clock.restart().asSeconds();
	//	saqo.Update(deltaTime);
	//	for (auto& platformCollider : platformColliders)
	//	{
	//		if (saqoCollider.CheckCollision(platformCollider, 0.0f))
	//		{
	//			std::cout << "1. Collision detected!" << std::endl;
	//			std::cout << "Y velocity right now: " << saqo.getPhysics().getVelocity().y << std::endl;

	//			if (saqo.getPhysics().getVelocity().y > 0)
	//			{
	//				std::cout << "2. Landed!" << std::endl;
	//				saqo.getPhysics().setOnGround(true);
	//				saqo.getPhysics().setVelocity(0.0f);
	//				sf::Vector2f currentVelocity = saqo.getPhysics().getVelocity();
	//				std::cout << "velocity after collision: (" << currentVelocity.x << currentVelocity.y << ")" << std::endl;
	//			}
	//		}
	//	}
	//	
	//	while (const std::optional event = window->pollEvent())
	//	{
	//		if (event->is<sf::Event::Closed>())
	//		{
	//			window->close();
	//		}
	//		else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
	//		{
	//			if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
	//			{
	//				window->close();
	//			}
	//		}
	//	}

	//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D))
	//	{
	//		saqoCollider.Move( 1.0f, 0.0f );	
	//	}
	//	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A))
	//	{
	//		saqoCollider.Move( -1.0f, 0.0f );
	//	}
	//	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Space))
	//	{
	//		if (saqo.getPhysics().isOnGround())
	//		{
	//			saqo.getPhysics().jump(500.0f);
	//		}
	//	}

	//	//Render
	//	window->clear(sf::Color(0xADD8E6));

	//	//Drawing
	//	window->draw(saqo);
	//	window->draw(square1);
	//	window->display();
	//	
	//	
	//}
	//
	//delete window;
	//return 0;
}