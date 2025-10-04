#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include "GameWorld.h"

class WorldRenderer
{
public:
	WorldRenderer(sf::RenderWindow& window, const std::map<int, Chunk>& worldData);

	void draw(const sf::View& view);

private:
	sf::RenderWindow& m_window;
	const std::map<int, Chunk>& m_worldData;
};

