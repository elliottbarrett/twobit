#ifndef BALL_H_INCLUDED
#define BALL_H_INCLUDED

#include "Entity.h"

class Ball : public Entity
{
public:
    Ball(unsigned int id, std::string name, std::vector<std::string> params);
    ~Ball();

    void update(float dt);
    std::string getEntityDescription();
    EntityType getEntityType();
    void handleEntityCollision(Entity* other);
    void handleHorizontalWorldCollision(WorldCollision c);
    void handleVerticalWorldCollision(WorldCollision c);

    void setActive(bool isActive);

private:
    void initParameters(std::vector<std::string> params);
    bool isActive;
};

#endif