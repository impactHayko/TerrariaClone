#include <iostream>
#include <SFML/Graphics.hpp>

<<<<<<< HEAD
enum directions { down, right, up, left };
=======
enum directions { right,left };
>>>>>>> f79cd64 (second commit)
int main()
{
	unsigned int width = 640;
	unsigned int height = 360;
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode({ width,height }), "Tutorials"); //creating window with title "tutorials"
	window->setFramerateLimit(60);

	sf::Texture texture;

<<<<<<< HEAD
	if (!texture.loadFromFile("Sprites/playersprite.png"))
	{
		std::cerr << "ERROR::COULD NOT LOAD FILE::Sprites/playersprite.png" << std::endl;
=======
	if (!texture.loadFromFile("Sprites/idlesprite.png"))
	{
		std::cerr << "ERROR::COULD NOT LOAD FILE::Sprites/idlesprite.png" << std::endl;
>>>>>>> f79cd64 (second commit)
		return -1;
	}
	sf::Sprite sprite(texture); //loading texture

<<<<<<< HEAD
	sf::IntRect dir[4];

	for (int i = 0; i < 4; ++i)
	{
		dir[i] = sf::IntRect({ {32 * i, 0}, { 32,32 } });
	}
	sprite.setTextureRect(dir[down]);
	sprite.setOrigin({ 16,16 });
=======
	//sf::IntRect dir[4];

	/*for (int i = 0; i < 4; ++i)
	{
		dir[i] = sf::IntRect({ {50 * i, 0}, { 50,50 } });
	}*/
	//sprite.setTextureRect(dir[down]);
	sprite.setOrigin({ 13,31 });
>>>>>>> f79cd64 (second commit)
	sprite.setPosition({ width / 2.0f, height / 2.0f });

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
			sprite.move({ 0.0f, 1.0f });
<<<<<<< HEAD
			sprite.setTextureRect(dir[down]);
=======
			//sprite.setTextureRect(dir[down]);
>>>>>>> f79cd64 (second commit)
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W))
		{
			sprite.move({ 0.0f, -1.0f });
<<<<<<< HEAD
			sprite.setTextureRect(dir[up]);
=======
			//sprite.setTextureRect(dir[up]);
>>>>>>> f79cd64 (second commit)
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D))
		{
			sprite.move({ 1.0f, 0.0f });
<<<<<<< HEAD
			sprite.setTextureRect(dir[right]);
=======
			sprite.setScale({ 1.f, 1.f });
			/*sprite.setTextureRect(dir[right]);*/
>>>>>>> f79cd64 (second commit)
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A))
		{
			sprite.move({ -1.0f, 0.0f });
<<<<<<< HEAD
			sprite.setTextureRect(dir[left]);
=======
			sprite.setScale({ -1.f, 1.f });
			//sprite.setTextureRect(dir[left]);
>>>>>>> f79cd64 (second commit)
		}

		//Render
		window->clear(sf::Color(0xADD8E6));

		//Drawing
		window->draw(sprite);

		window->display();
	}

	delete window;
	return 0;
}