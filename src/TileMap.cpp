#include "TileMap.h"

#include <iostream>
#include <fstream>

TileMap::TileMap()
{

}

bool TileMap::load()
{
	std::string levelFile = "assets/TwoBit.tbw";
	std::fstream levelStream(levelFile, std::ios_base::in);
	int levelReadIndex = 0;
	int levelReadValue;

	levelStream >> levelWidth;
	levelStream >> levelHeight;

	level = new int[levelWidth * levelHeight];
	tileSize = sf::Vector2u(16, 16);

	// Set all tiles to 0 in case level is just width and height or not enough tiles...
	for (int i = 0; i < levelWidth * levelHeight; i++)
	{
		level[i] = 0;
	}

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
			updateTileQuad(i, j);
		}
	}
}

void TileMap::updateTileQuad(int x, int y)
{
	int currentTileIndex = level[x + y * levelWidth];

	int tu = currentTileIndex % (tileTexture.getSize().x / tileSize.x);
	int tv = currentTileIndex / (tileTexture.getSize().x / tileSize.x);

	sf::Vertex* quad = &vertices[(x + y * levelWidth) * 4];

    // define its 4 corners
    quad[0].position = sf::Vector2f(x * tileSize.x, y * tileSize.y);
    quad[1].position = sf::Vector2f((x + 1) * tileSize.x, y * tileSize.y);
    quad[2].position = sf::Vector2f((x + 1) * tileSize.x, (y + 1) * tileSize.y);
    quad[3].position = sf::Vector2f(x * tileSize.x, (y + 1) * tileSize.y);

    // define its 4 texture coordinates
    quad[3].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
    quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
    quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
    quad[0].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
}

bool TileMap::setTile(int x, int y, int val)
{
	int currentTileValue = level[y * levelWidth + x];

	if (currentTileValue == val)
	{
		return true;
	}

	level[y * levelWidth + x] = val;
	updateTileQuad(x, y);
	return true;
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    states.texture = &tileTexture;
    target.draw(vertices, states);
}
