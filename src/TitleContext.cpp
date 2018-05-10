#include "TitleContext.h"

#include <iostream>

TitleContext::TitleContext()
{
    backgroundTexture.loadFromFile("assets/Title.png");
    backgroundSprite = sf::Sprite(backgroundTexture);
    backgroundSprite.setScale(4,4);
}

void TitleContext::update(float dt)
{

}

void TitleContext::render(sf::RenderWindow &window)
{
    window.draw(backgroundSprite);
}