#include "TileMap.h"

#include <iostream>

TileMap::TileMap()
{

}

bool TileMap::load()
{
	const int width = 10;
	const int height = 9;
	const int level[] = 
	{
		12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
		12,  0,  0,  0,  0,  0,  0,  0,  0, 12,
		12,  0,  0,  0,  0,  0,  0,  0,  0, 12,
		12,  0,  0,  0,  0,  0,  0,  0,  0, 12,
		12,  0,  0,  0,  0,  0,  0,  0,  0, 12,
		12,  0,  0,  0,  0,  0,  0,  0,  0, 12,
		12,  0,  0,  0,  0,  0,  0,  0,  0, 12,
		12,  0,  0,  0,  0,  1,  2,  2,  2, 12,
		12, 12, 12, 12, 12, 12, 12, 12, 12, 12
	};
	sf::Vector2u tileSize(16, 16);

	vertices.setPrimitiveType(sf::Quads);
	vertices.resize(width * height * 4);
	
	if (!tileTexture.loadFromFile("assets/LevelTileset.png"))
	{
		return false;
	}

	for (unsigned int i = 0; i < width; i++)
	{
		for (unsigned int j = 0; j < height; j++)
		{
			int currentTileIndex = level[i + j * width];

			int tu = currentTileIndex % (tileTexture.getSize().x / tileSize.x);
			int tv = currentTileIndex / (tileTexture.getSize().x / tileSize.x);

			sf::Vertex* quad = &vertices[(i + j * width) * 4];

            // define its 4 corners
            quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
            quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
            quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

            // define its 4 texture coordinates
            quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
            quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
            quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
		}
	}
    
	return true;
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    states.texture = &tileTexture;
    target.draw(vertices, states);
}
