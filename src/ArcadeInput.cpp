#include "ArcadeInput.h"

#include <SFML/Window.hpp>

InputState ArcadeInput::getPlayerOneState()
{
    InputState state;
    unsigned int direction = 0;
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        direction |= (unsigned int)JoyDirection::LEFT;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        direction |= (unsigned int)JoyDirection::RIGHT;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
    {
        direction |= (unsigned int)JoyDirection::UP;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
    {
        direction |= (unsigned int)JoyDirection::DOWN;
    }

    state.direction = (JoyDirection) direction;
    state.leftButton = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z);
    state.rightButton = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z);

    return state;
}

InputState ArcadeInput::getPlayerTwoState()
{
    InputState state;
    unsigned int direction = 0;
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::J))
    {
        direction |= (unsigned int)JoyDirection::LEFT;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L))
    {
        direction |= (unsigned int)JoyDirection::RIGHT;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::I))
    {
        direction |= (unsigned int)JoyDirection::UP;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::K))
    {
        direction |= (unsigned int)JoyDirection::DOWN;
    }

    state.direction = (JoyDirection) direction;
    state.leftButton = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::N);
    state.rightButton = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::M);

    return state;
}

bool ArcadeInput::isWhiteButtonPressed()
{
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape);
}