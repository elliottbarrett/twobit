#include "NPC.h"

#include <iostream>

NPC::NPC(unsigned int id, std::string name, std::vector<std::string> params) :
    Entity(id, name, params)
{

}

NPC::~NPC()
{

}

void NPC::initParameters(std::vector<std::string> params)
{
    Entity::initParameters(params);

    
}


EntityType NPC::getEntityType()
{
    return ET_NPC;
}

std::string NPC::getEntityDescription()
{
    return std::to_string(id) + " NPC " + name + "\n"
        + getCommonParameters()
        + writeParameter("texture", "poordog.png")
        + writeParameter("animation", "poordog_talking");
}

void NPC::update(float dt)
{
    Entity::update(dt);
}

void NPC::handleEntityCollision(Entity *other)
{
    switch (other->getEntityType())
    {
        case ET_PLAYER:

        default:
            break;
    }
}