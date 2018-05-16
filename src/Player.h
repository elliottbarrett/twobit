#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "Entity.h"

class Player : public Entity
{
public:
    Player(std::string name);
    ~Player();
    void update(float dt);

    sf::FloatRect getCollisionBounds();
    void handleWorldCollision(bool didCollide);

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void updatePhysics();

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