#include "TileMap.h"

#include <iostream>
#include <fstream>

TileMap::TileMap()
{
    topLeftCollisionRect = sf::RectangleShape(sf::Vector2f(16,16));
    topLeftCollisionRect.setFillColor(sf::Color::Transparent);
    topLeftCollisionRect.setOutlineColor(sf::Color(0,255,0));
    topLeftCollisionRect.setOutlineThickness(-1);
    topRightCollisionRect = sf::RectangleShape(sf::Vector2f(16,16));
    topRightCollisionRect.setFillColor(sf::Color::Transparent);
    topRightCollisionRect.setOutlineColor(sf::Color(0,255,0));
    topRightCollisionRect.setOutlineThickness(-1);
    bottomLeftCollisionRect = sf::RectangleShape(sf::Vector2f(16,16));
    bottomLeftCollisionRect.setFillColor(sf::Color::Transparent);
    bottomLeftCollisionRect.setOutlineColor(sf::Color(0,255,0));
    bottomLeftCollisionRect.setOutlineThickness(-1);
    bottomRightCollisionRect = sf::RectangleShape(sf::Vector2f(16,16));
    bottomRightCollisionRect.setFillColor(sf::Color::Transparent);
    bottomRightCollisionRect.setOutlineColor(sf::Color(0,255,0));
    bottomRightCollisionRect.setOutlineThickness(-1);
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

bool TileMap::checkWorldCollisions(sf::FloatRect rect)
{
    int tileMapLeft = (int)(rect.left / 16);
    int tileMapRight = (int)((rect.left + rect.width) / 16);
    int tileMapTop = (int)((rect.top + rect.height) / 16);
    int tileMapBottom = (int)((rect.top) / 16);

    int topLeftTile = tileMapLeft + tileMapTop * levelWidth;
    int topRightTile = tileMapRight + tileMapTop * levelWidth;
    int bottomLeftTile = tileMapLeft + tileMapBottom * levelWidth;
    int bottomRightTile = tileMapRight + tileMapBottom * levelWidth;

    // TODO: Better level defined tile collision info. For now, 0 is no collision, 1 is collision
    // TODO: Do something about flipped Y-axis (top-left is rendering on bottom and vice-versa)

    bool collided = false;

    // check top-left collision
    topLeftCollisionRect.setPosition(tileMapLeft * 16.0, tileMapTop * 16.0);

    if (topLeftTile >= 0 && level[topLeftTile] != 0)
    {
        topLeftCollisionRect.setOutlineColor(sf::Color(255,0,0));
        collided = true;
    }
    else
    {
        topLeftCollisionRect.setOutlineColor(sf::Color(0,255,0));
    }

    // check top-right collision
    topRightCollisionRect.setPosition(tileMapRight * 16.0, tileMapTop * 16.0);

    if (topRightTile >= 0 && level[topRightTile] != 0)
    {
        topRightCollisionRect.setOutlineColor(sf::Color(255,0,0));
        collided = true;
    }
    else
    {
        topRightCollisionRect.setOutlineColor(sf::Color(0,255,0));
    }

    // check bottom-left collision
    bottomLeftCollisionRect.setPosition(tileMapLeft * 16.0, tileMapBottom * 16.0);

    if (bottomLeftTile >= 0 && level[bottomLeftTile] != 0)
    {
        bottomLeftCollisionRect.setOutlineColor(sf::Color(255,0,0));
        collided = true;
    }
    else
    {
        bottomLeftCollisionRect.setOutlineColor(sf::Color(0,255,0));
    }

    // check bottom-right collision
    bottomRightCollisionRect.setPosition(tileMapRight * 16.0, tileMapBottom * 16.0);

    if (bottomRightTile >= 0 && level[bottomRightTile] != 0)
    {
        bottomRightCollisionRect.setOutlineColor(sf::Color(255,0,0));
        collided = true;
    }
    else
    {
        bottomRightCollisionRect.setOutlineColor(sf::Color(0,255,0));
    }

    return collided;
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    states.texture = &tileTexture;
    target.draw(vertices, states);
    target.draw(topLeftCollisionRect, states);
    target.draw(topRightCollisionRect, states);
    target.draw(bottomLeftCollisionRect, states);
    target.draw(bottomRightCollisionRect, states);
}
