#ifndef TITLECONTEXT_H_INCLUDED
#define TITLECONTEXT_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "GameContext.h"

class TitleContext : public GameContext
{
public:
    TitleContext();
    virtual void update(float dt);
    virtual void render(sf::RenderWindow &window);

private:
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
};

#endif