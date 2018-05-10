#include "GameContext.h"

#include <iostream>

GameContext::GameContext()
{
}

void GameContext::update(float dt)
{
    std::cout << "GameContext" << std::endl;
}

void GameContext::render(sf::RenderWindow &window)
{
}