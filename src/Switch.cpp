#include "Switch.h"

Switch::Switch(unsigned int id, std::string name, std::vector<std::string> params) :
    Entity(id, name, params)
{
    initParameters(params);
}

Switch::~Switch()
{

}

void Switch::initParameters(std::vector<std::string> params)
{
    Entity::initParameters(params);
}

EntityType Switch::getEntityType()
{
    return ET_SWITCH;
}

std::string Switch::getEntityDescription()
{
    // auto standardComponent = Entity::getEntityDescription();

    return "SWITCH TODO\n";
}

void Switch::update(float dt)
{

}

void Switch::handleEntityCollision(Entity *other)
{

}
