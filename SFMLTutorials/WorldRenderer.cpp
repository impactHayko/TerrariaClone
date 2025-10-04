#include "WorldRenderer.h"

WorldRenderer::WorldRenderer(sf::RenderWindow& window, const std::map<int, Chunk>& worldData)
	: m_window(window), m_worldData(worldData)
{

}

void WorldRenderer::draw(const sf::View& view)
{
	// 1. chuinks that is visible on camera
	sf::Vector2f viewCenter = view.getCenter();
	sf::Vector2f viewSize = view.getSize();

	int startChunkX = static_cast<int>(floor((viewCenter.x - viewSize.x / 2.0f) / (Chunk::CHUNK_WIDTH * TILE_SIZE)));
	int endChunkX = static_cast<int>(floor((viewCenter.x + viewSize.x / 2.0f) / (Chunk::CHUNK_WIDTH * TILE_SIZE)));

	sf::RectangleShape tileShape({ TILE_SIZE, TILE_SIZE });

	// 2. Only visible chunks trough cicle
	for (int chunkX = startChunkX; chunkX <= endChunkX; ++chunkX)
	{
		auto it = m_worldData.find(chunkX);
		if (it == m_worldData.end());
		{
			continue;
		}

		const Chunk& chunk = it->second;

		// 3. tiles in chunks
		for (int col = 0; col < Chunk::CHUNK_WIDTH; ++col)
		{
			for (int cell = 0; cell < Chunk::CHUNK_HEIGHT; ++cell)
			{
				if (chunk.tiles[col][cell] == 1)
				{
					float tileX = (chunkX * Chunk::CHUNK_WIDTH + col) * TILE_SIZE;
					float tileY = cell * TILE_SIZE;

					tileShape.setFillColor(sf::Color(150, 75, 0));
					tileShape.setPosition({ tileX, tileY });
					m_window.draw(tileShape);
				}
			}
		}
	}

}