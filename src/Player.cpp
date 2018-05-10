#include "Player.h"
#include "ArcadeInput.h"

Player::Player()
{
    AnimatedSprite();
    collisionRect = sf::RectangleShape(sf::Vector2f(16,16));
    collisionRect.setFillColor(sf::Color::Transparent);
    collisionRect.setOutlineColor(sf::Color(255,0,255));
    collisionRect.setOutlineThickness(-1);
}

Player::~Player()
{
}

void Player::update(float dt)
{
    AnimatedSprite::update(dt);

    InputState input = ArcadeInput::getPlayerOneState();

    if (input.direction & JoyDirection::RIGHT)
    {
        move(1,0);
    }
    if (input.direction & JoyDirection::UP)
    {
        move(0,1);
    }
    if (input.direction & JoyDirection::LEFT)
    {
        move(-1,0);
    }
    if (input.direction & JoyDirection::DOWN)
    {
        move(0,-1);
    }

}

sf::FloatRect Player::getCollisionBounds()
{
    auto transform = getTransform();
    sf::FloatRect bounds = transform.transformRect(sf::FloatRect(1,0,14,16));
    return bounds;
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    AnimatedSprite::draw(target, states);
    states.transform *= getTransform();
    target.draw(collisionRect, states);
}