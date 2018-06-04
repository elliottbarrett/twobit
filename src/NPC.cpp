#include "NPC.h"
#include "UI.h"

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
    UI::hideMessage();
}

void NPC::handleEntityCollision(Entity *other)
{
    switch (other->getEntityType())
    {
        case ET_PLAYER:
            UI::showMessage("This works\nWhat a great idea\nP.ONE gets stick\nP.TWO gets ball");
            break;
        default:
            break;
    }
}