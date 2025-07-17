#include <iostream>
#include <SFML/Graphics.hpp>
#include "Collider.h"


int main()
{
	unsigned int width = 800;
	unsigned int height = 600;
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode({ width,height }), "Tutorials"); //creating window with title "tutorials"
	window->setFramerateLimit(60);

	sf::Texture texture;

	//CREATING SQUARE
	sf::RectangleShape square({ 60.f, 60.f });
	square.setFillColor(sf::Color::Black);
	square.setOrigin({30.f,30.f });
	square.setPosition({ 400,300 });

	//CREATING SQUARE
	sf::RectangleShape square1({ 60.f, 60.f });
	square1.setFillColor(sf::Color::Red);
	square1.setOrigin({ 30.f,30.f });
	square1.setPosition({ 400,450 });

	Collider collider(square);

	Collider collider1(square1);
	
	
	while (window->isOpen())
	{
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



		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::S))
		{
			collider.CheckCollision(collider1, 0.0f);
			collider.Move( 0.0f, 1.0f );
			
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W))
		{
			collider.CheckCollision(collider1, 0.0f);
			collider.Move( 0.0f, -1.0f );
			
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D))
		{
			collider.CheckCollision(collider1, 0.0f);
			collider.Move( 1.0f, 0.0f );
			
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A))
		{
			collider.CheckCollision(collider1, 0.0f);
			collider.Move( -1.0f, 0.0f );
		
		}

		//Render
		window->clear(sf::Color(0xADD8E6));

		//Drawing
		window->draw(square);
		window->draw(square1);
		//window->draw(circle);
		window->display();
		
		
	}
	
	delete window;
	return 0;
}