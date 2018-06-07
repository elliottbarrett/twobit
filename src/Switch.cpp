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

        if (key == "type")
        {
            if (value == "floor")
            {
                type = ST_FLOOR;
            }
            else if (value == "toggle")
            {
                type = ST_TOGGLE;
            }
        }
    }
}

EntityType Switch::getEntityType()
{
    return ET_SWITCH;
}

std::string Switch::getEntityDescription()
{
    std::string switchParams;

    if (type == ST_FLOOR)
    {
        switchParams = writeParameter("animation", "floor_switch_inactive");
        switchParams += writeParameter("type", "floor");
    }
    else if (type == ST_TOGGLE)
    {
        switchParams = writeParameter("animation", "toggle_switch_inactive");
        switchParams += writeParameter("type", "toggle");
    }

    return std::to_string(id) + " Switch " + name + "\n"
        + getCommonParameters()
        + writeParameter("texture", "world_entities.png")
        + switchParams;
}

void Switch::update(float dt)
{
    Entity::update(dt);

    switch (type)
    {
    case ST_FLOOR:
        playAnimation("floor_switch_inactive");
        pressed = false;
        break;
    case ST_TOGGLE:
        break;
    }
}

bool Switch::isPressed()
{
    return pressed;
}

void Switch::handleEntityCollision(Entity *other)
{
    if (type == ST_FLOOR)
    {
        switch (other->getEntityType())
        {
        case ET_PLAYER:
            playAnimation("floor_switch_active");
            pressed = true;
            break;
        default:
            break;
        }
    } 
    else if (type == ST_TOGGLE)
    {
        switch (other->getEntityType())
        {
        case ET_PLAYER:
            playAnimationLooped("toggle_switch_active");
            pressed = true;
            break;
        default:
            break;
        }
    }

}
