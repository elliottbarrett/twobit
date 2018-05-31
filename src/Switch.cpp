#include "Switch.h"
#include "Door.h"
#include "Entities.h"

#include <iostream>

Switch::Switch(unsigned int id, std::string name, std::vector<std::string> params) :
    Entity(id, name, params), currentState(SwitchState::UP), previousState(SwitchState::UP)
{
    initParameters(params);
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

        if (key == "opensDoor") targetDoor = (Door*) Entities::getById(std::stoi(value));
    }
}

EntityType Switch::getEntityType()
{
    return ET_SWITCH;
}

std::string Switch::getEntityDescription()
{
    // auto standardComponent = Entity::getEntityDescription();
    return std::to_string(id) + " Switch " + name + "\n"
        + getCommonParameters()
        + writeParameter("texture", "door.png")
        + writeParameter("animation", "switch_inactive")
        + writeParameter("opensDoor", targetDoor->getId());
}

void Switch::update(float dt)
{
    Entity::update(dt);

    if (currentState == SwitchState::UP && previousState == SwitchState::DOWN)
    {
        targetDoor->close();
    }
    else if (currentState == SwitchState::DOWN && previousState == SwitchState::UP)
    {
        targetDoor->open();
    }

    previousState = currentState;

    currentState = SwitchState::UP;
    playAnimation("switch_inactive");
}

void Switch::handleEntityCollision(Entity *other)
{
    switch (other->getEntityType())
    {
    case ET_PLAYER:
        playAnimation("switch_active");
        currentState = SwitchState::DOWN;
        break;
    default:
        break;
    }

}
