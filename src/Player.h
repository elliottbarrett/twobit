#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "Entity.h"

class Player : public Entity
{
public:
    Player(unsigned int id, std::string name, std::vector<std::string> params);
    ~Player();
    void update(float dt);
    std::string getEntityDescription();

    sf::FloatRect getCollisionBounds();
    void handleWorldCollision(bool didCollide);


private:
    void initParameters(std::vector<std::string> params);
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