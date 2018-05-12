#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "AnimatedSprite.h"

class Player : public AnimatedSprite
{
public:
    Player(int playerNumber);
    ~Player();
    void update(float dt);

    sf::FloatRect getCollisionBounds();
    void handleWorldCollision(bool didCollide);

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void updatePhysics();

    const float walkSpeed = 80.0;
    const float jumpSpeed = 250.0;
    const float gravity = -750.0;

    int playerNumber;

    sf::Vector2f velocity;
    sf::RectangleShape collisionRect;

    bool isOnGround;
    bool wasOnGround;
    bool isAtCeiling;
    bool wasAtCeiling;
    bool isPushingLeftWall;
    bool wasPushingLeftWall;
    bool isPushingRightWall;
    bool wasPushingRightWall;
};

#endif