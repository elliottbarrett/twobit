#include "TileMap.h"

#include <iostream>
#include <fstream>

TileMap::TileMap()
{

}

bool TileMap::load()
{
	// TODO: Read width and height from file
	levelWidth = 10;
	levelHeight = 9;
	level = new int[90];
	tileSize = sf::Vector2u(16, 16);

	std::string levelFile = "assets/TwoBit.tbw";
	std::fstream levelStream(levelFile, std::ios_base::in);
	int levelReadIndex = 0;
	int levelReadValue;

	levelStream >> levelWidth;
	levelStream >> levelHeight;

	while (levelStream >> levelReadValue)
	{
		level[levelReadIndex] = levelReadValue;
		levelReadIndex++;
	}

	vertices.setPrimitiveType(sf::Quads);
	vertices.resize(levelWidth * levelHeight * 4);
	
	if (!tileTexture.loadFromFile("assets/LevelTileset.png"))
	{
		return false;
	}

	build();
    
	return true;
}

bool TileMap::save()
{
	std::ofstream outputStream;
	int tileCount = levelWidth * levelHeight;

	outputStream.open("assets/TwoBit.tbw");
	outputStream << levelWidth << " " << levelHeight << " ";

	for (int i = 0; i < levelWidth * levelHeight; i++)
	{
		outputStream << level[i] << " ";
	}

	outputStream.close();
}

void TileMap::build()
{
	for (unsigned int i = 0; i < levelWidth; i++)
	{
		for (unsigned int j = 0; j < levelHeight; j++)
		{
			int currentTileIndex = level[i + j * levelWidth];

			int tu = currentTileIndex % (tileTexture.getSize().x / tileSize.x);
			int tv = currentTileIndex / (tileTexture.getSize().x / tileSize.x);

			sf::Vertex* quad = &vertices[(i + j * levelWidth) * 4];

            // define its 4 corners
            quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
            quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
            quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

            // define its 4 texture coordinates
            quad[3].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
            quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
            quad[0].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
		}
	}
}

bool TileMap::setTile(int x, int y, int val)
{
	int currentTileValue = level[y * levelWidth + x];

	if (currentTileValue == val)
	{
		return true;
	}

	level[y * levelWidth + x] = val;
	build();
	return true;
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    states.texture = &tileTexture;
    target.draw(vertices, states);
}
