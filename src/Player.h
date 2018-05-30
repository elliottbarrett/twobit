#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "Entity.h"

#include "TileMap.h"

class Player : public Entity
{
public:
    Player(unsigned int id, std::string name, std::vector<std::string> params);
    ~Player();
    void update(float dt);
    std::string getEntityDescription();

    void handleHorizontalWorldCollision(WorldCollision collision);
    void handleVerticalWorldCollision(WorldCollision collision);
    void handleEntityCollision(Entity *other);
    void drawInspectorWidgets();
    EntityType getEntityType();

private:
    void initParameters(std::vector<std::string> params);
    void updatePhysics();

    int playerNumber;

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