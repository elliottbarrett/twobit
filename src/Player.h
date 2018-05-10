#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "AnimatedSprite.h"

class Player : public AnimatedSprite
{
public:
    Player();
    ~Player();
    void update(float dt);

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    sf::RectangleShape collisionRect;
};

#endif