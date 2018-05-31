#ifndef DOOR_H_INCLUDED
#define DOOR_H_INCLUDED

#include "Entity.h"

class Switch;

class Door : public Entity
{
public:
    Door(unsigned int id, std::string name, std::vector<std::string> params);
    ~Door();

    void update(float dt);
    std::string getEntityDescription();
    EntityType getEntityType();
    void handleEntityCollision(Entity* other);

    void open();
    void close();

private:
    void initParameters(std::vector<std::string> params);
    std::vector<Switch*> openSwitches;
    int openSwitchesRequired;
};

#endif