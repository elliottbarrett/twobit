#ifndef TILEMAP_H_INCLUDED
#define TILEMAP_H_INCLUDED

#include <SFML/Graphics.hpp>

class TileMap : public sf::Drawable, public sf::Transformable
{
public:
	TileMap();
bool load();

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    sf::Texture tileTexture;
    sf::VertexArray vertices;
};

#endif