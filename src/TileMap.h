#ifndef TILEMAP_H_INCLUDED
#define TILEMAP_H_INCLUDED

#include <SFML/Graphics.hpp>

class TileMap : public sf::Drawable, public sf::Transformable
{
public:
    TileMap();
    bool load();
    bool save();
    bool setTile(int x, int y, int val);
    bool checkWorldCollisions(sf::FloatRect rect);

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual void build();
    void updateTileQuad(int x, int y);

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