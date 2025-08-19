#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Collider.h"
#include "Animation.h"
#include "Player.h"

int main()
{
	unsigned int width = 800;
	unsigned int height = 600;
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode({ width,height }), "Tutorials"); //creating window with title "tutorials"
	window->setFramerateLimit(60);
	sf::Texture playerTexture;
	playerTexture.loadFromFile("Sprites/playersprite.png");

	std::vector<Collider> platformColliders;

	Player saqo(&playerTexture, sf::Vector2u(7,6), 0.3f);

	//CREATING SQUARE
	sf::RectangleShape square1({ 800.f, 60.f });
	sf::Vector2f size = square1.getSize();
	square1.setFillColor(sf::Color::Red);
	square1.setOrigin({ size.x / 2, size.y / 2 });
	square1.setPosition({ 400,450 });

	Collider collider1(square1);
	platformColliders.push_back(collider1);
	
	Collider saqoCollider(saqo.body);

	//deltaTime
	float deltaTime = 0.0f;
	sf::Clock clock;
	
	while (window->isOpen())
	{
		deltaTime = clock.restart().asSeconds();
		saqo.Update(deltaTime);
		for (auto& platformCollider : platformColliders)
		{
			saqoCollider.CheckCollision(platformCollider, 0.f);
		}
		
		while (const std::optional event = window->pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window->close();
			}
			else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
			{
				if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
				{
					window->close();
				}
			}
		}

		 if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D))
		{
			saqoCollider.Move( 1.0f, 0.0f );	
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A))
		{
			saqoCollider.Move( -1.0f, 0.0f );
		}

		//Render
		window->clear(sf::Color(0xADD8E6));

		//Drawing
		window->draw(saqo);
		window->draw(square1);
		window->display();
		
		
	}
	
	delete window;
	return 0;
}