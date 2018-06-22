#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "Entity.h"

#include "TileMap.h"
#include "ArcadeInput.h"


class Ball;

enum PlayerItem
{
    PI_NONE,
    PI_STICK,
    PI_BALL
};

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
    PlayerItem getCurrentItem();
    void giveItem(PlayerItem item);

private:
    void initParameters(std::vector<std::string> params);
    void updatePhysics();
    void tryUseCurrentItem();
    void switchItem();
    void ignoreInputForSeconds(float t);

    int playerNumber;
    PlayerItem currentItem;

    Ball* ball;

    bool isOnGround;
    bool wasOnGround;
    bool isAtCeiling;
    bool wasAtCeiling;
    bool isPushingLeftWall;
    bool wasPushingLeftWall;
    bool isPushingRightWall;
    bool wasPushingRightWall;
    int framesSinceJump;

    InputState lastFrameInput;

    // Input ignoring
    float ignoreInputTime;
    float ignoreInputElapsed;

    float invincibilityTime;
    float invincibilityTimeElapsed;

    float jumpModifier;

    // Inventory
    std::vector<PlayerItem> items;
};

#endif