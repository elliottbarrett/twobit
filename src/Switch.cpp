#include "Switch.h"
#include "Door.h"
#include "Entities.h"

#include <iostream>

Switch::Switch(unsigned int id, std::string name, std::vector<std::string> params) :
    Entity(id, name, params)
{
}

Switch::~Switch()
{

}

void Switch::initParameters(std::vector<std::string> params)
{
    Entity::initParameters(params);

    for (auto it : params)
    {
        auto key = it.substr(0, it.find(" "));
        auto value = it.substr(it.find(" ") + 1);
    }
}

EntityType Switch::getEntityType()
{
    return ET_SWITCH;
}

std::string Switch::getEntityDescription()
{
    return std::to_string(id) + " Switch " + name + "\n"
        + getCommonParameters()
        + writeParameter("texture", "world_entities.png")
        + writeParameter("animation", "switch_inactive");
}

void Switch::update(float dt)
{
    Entity::update(dt);
    playAnimation("switch_inactive");
    pressed = false;
}

bool Switch::isPressed()
{
    return pressed;
}

void Switch::handleEntityCollision(Entity *other)
{
    switch (other->getEntityType())
    {
    case ET_PLAYER:
        playAnimation("switch_active");
        pressed = true;
        break;
    default:
        break;
    }

}
