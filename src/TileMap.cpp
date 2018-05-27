#include "TileMap.h"

#include <iostream>
#include <fstream>
#include <math.h>
#include "Settings.h"
#include "Entity.h"

int SmartPaintConfig::getTileIndexForNeighbouringFills(bool top, bool left, bool right, bool bottom)
{
    unsigned int state = 0;
    state |= (top ? 0b1000 : 0b0000);
    state |= (left ? 0b0100 : 0b0000);
    state |= (right ? 0b0010 : 0b0000);
    state |= (bottom ? 0b0001 : 0b0000);

    switch (state & 0xf)
    {
        case 0b0000:
            return loneBlock;
        case 0b0001:
            return columnTop;
        case 0b0010:
            return platformLeft;
        case 0b0011:
            return topLeftCorner;
        case 0b0100:
            return platformRight;
        case 0b0101:
            return topRightCorner;
        case 0b0110:
            return platformMid;
        case 0b0111:
            return topLine;
        case 0b1000:
            return columnBottom;
        case 0b1001:
            return columnMid;
        case 0b1010:
            return bottomLeftCorner;
        case 0b1011:
            return leftLine;
        case 0b1100:
            return bottomRightCorner;
        case 0b1101:
            return rightLine;
        case 0b1110:
            return bottomLine;
        case 0b1111:
            return fillInner;
    }

    // Unreachable
    return 0;
}

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

    outputStream.open("assets/TwoBit.tbw");

    if (!outputStream.is_open())
    {
        return false;
    }

    outputStream << levelWidth << " " << levelHeight << " ";

    for (int i = 0; i < levelWidth * levelHeight; i++)
    {
        outputStream << level[i] << " ";
    }

    outputStream.close();
    return true;
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

    quad[0].position = sf::Vector2f(x * tileSize.x, y * tileSize.y);
    quad[1].position = sf::Vector2f((x + 1) * tileSize.x, y * tileSize.y);
    quad[2].position = sf::Vector2f((x + 1) * tileSize.x, (y + 1) * tileSize.y);
    quad[3].position = sf::Vector2f(x * tileSize.x, (y + 1) * tileSize.y);

    quad[0].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
    quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
    quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
    quad[3].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
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

void TileMap::smartPaint(int x, int y, bool fill, SmartPaintConfig config)
{
    if (fill)
    {
        setTile(x, y, config.loneBlock);
        smartTileReplace(x, y, config);
    }
    else
    {
        setTile(x, y, 0);
    }

    smartTileReplace(x-1, y, config);
    smartTileReplace(x+1, y, config);
    smartTileReplace(x, y-1, config);
    smartTileReplace(x, y+1, config);
}

void TileMap::smartTileReplace(int x, int y, SmartPaintConfig config)
{
    if (x < 0 || x >= levelWidth || y < 0 || y >= levelHeight)
    {
        return;
    }
    else if (level[x + levelWidth * y] == 0)
    {
        return;
    }

    bool leftFilled = getTile(x-1, y) != 0;
    bool rightFilled = getTile(x+1, y) != 0;
    bool topFilled = getTile(x, y+1) != 0;
    bool bottomFilled = getTile(x, y-1) != 0;

    setTile(x, y, config.getTileIndexForNeighbouringFills(topFilled, leftFilled, rightFilled, bottomFilled));
}

int TileMap::getTile(int x, int y)
{
    if (x < 0 || y < 0 || x >= levelWidth || y >= levelHeight) 
    {
        return -1;
    }

    return level[x + y * levelWidth];
}

int TileMap::getTile(float worldX, float worldY)
{
    return getTile((int)(worldX / 16), (int)(worldY / 16));
}

WorldCollision TileMap::checkHorizontalWorldCollisions(Entity *entity)
{
    WorldCollision collision;
    auto bounds = entity->getCollisionBounds();
    auto velocity = entity->getVelocity();

    if (velocity.x > 0)
    {
        int topTile = getTile(bounds.left + bounds.width, bounds.top + bounds.height);
        int bottomTile = getTile(bounds.left + bounds.width, bounds.top);

        collision.hitRight = topTile != 0 || bottomTile != 0;
        collision.xIntersectionDistance = fmod(bounds.left + bounds.width, 16);
    }
    else if (velocity.x < 0)
    {
        int topTile = getTile(bounds.left, bounds.top + bounds.height);
        int bottomTile = getTile(bounds.left, bounds.top);

        collision.hitLeft = topTile != 0 || bottomTile != 0;
        collision.xIntersectionDistance = fmod(bounds.left, 16) - 16;
    }

    return collision;
}

WorldCollision TileMap::checkVerticalWorldCollisions(Entity *entity)
{
    WorldCollision collision;
    auto bounds = entity->getCollisionBounds();
    auto velocity = entity->getVelocity();

    if (velocity.y > 0)
    {
        int leftTile = getTile(bounds.left, bounds.top + bounds.height);
        int rightTile = getTile(bounds.left + bounds.width, bounds.top + bounds.height);

        collision.hitTop = leftTile != 0 || rightTile != 0;
        collision.yIntersectionDistance = fmod(bounds.top + bounds.height, 16);
    }
    else if (velocity.y <= 0)
    {
        int leftTile = getTile(bounds.left, bounds.top);
        int rightTile = getTile(bounds.left + bounds.width, bounds.top);

        collision.hitBottom = leftTile != 0 || rightTile != 0;
        collision.yIntersectionDistance = fmod(bounds.top, 16);
    }

    return collision;
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    states.texture = &tileTexture;
    target.draw(vertices, states);
}
