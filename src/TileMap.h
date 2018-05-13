#ifndef TILEMAP_H_INCLUDED
#define TILEMAP_H_INCLUDED

#include <SFML/Graphics.hpp>

struct SmartPaintConfig
{
    int topLeftCorner;
    int topLine;
    int topRightCorner;
    int leftLine;
    int rightLine;
    int fillInner;
    int bottomLeftCorner;
    int bottomRightCorner;
    int bottomLine;
    int platformLeft;
    int platformMid;
    int platformRight;
    int columnTop;
    int columnMid;
    int columnBottom;
    int loneBlock;

    int getTileIndexForNeighbouringFills(bool top, bool bottom, bool left, bool right);

    static SmartPaintConfig getDefault()
    {
        SmartPaintConfig c;
        c.topLeftCorner = 1;
        c.topLine = 2;
        c.topRightCorner = 3;
        c.platformLeft = 4;
        c.platformMid = 5;
        c.platformRight = 6;
        c.loneBlock = 10;
        c.leftLine = 11;
        c.fillInner = 12;
        c.rightLine = 13;
        c.bottomLeftCorner = 21;
        c.bottomLine = 22;
        c.bottomRightCorner = 23;
        c.columnTop = 14;
        c.columnMid = 24;
        c.columnBottom = 34;
    
        return c;
    }
};

class TileMap : public sf::Drawable, public sf::Transformable
{
public:
    TileMap();
    bool load();
    bool save();
    bool smartPaint(int x, int y, bool fill, SmartPaintConfig config);
    bool setTile(int x, int y, int val);
    int getTile(int x, int y);
    bool checkWorldCollisions(sf::FloatRect rect);

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual void build();
    void updateTileQuad(int x, int y);
    void smartTileReplace(int x, int y, SmartPaintConfig config);

    sf::Texture tileTexture;
    sf::VertexArray vertices;
    sf::Vector2u tileSize;

    sf::RectangleShape topLeftCollisionRect;
    sf::RectangleShape topRightCollisionRect;
    sf::RectangleShape bottomLeftCollisionRect;
    sf::RectangleShape bottomRightCollisionRect;

    int* level;
    int levelWidth;
    int levelHeight;
};

#endif