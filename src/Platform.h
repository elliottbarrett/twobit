#ifndef PLATFORM_H_INCLUDED
#define PLATFORM_H_INCLUDED

#include "Entity.h"

class Switch;

class Platform : public Entity
{
public:
    Platform(unsigned int id, std::string name, std::vector<std::string> params);
    ~Platform();

    void initParameters(std::vector<std::string> params);
    void update(float dt);
    std::string getEntityDescription();
    EntityType getEntityType();
    void handleEntityCollision(Entity* other);

    void drawInspectorWidgets();

private:
    
    std::vector<sf::Vector2f> waypoints;
    int currentWaypoint;
    float speed;
    float waypointPauseTime;
    float timeAtCurrentWaypoint;
    bool isAtWaypoint;
    bool isWaypointDirectionAscending;

    int moveSwitchesRequired;
    std::vector<Switch*> moveSwitches;
};

#endif