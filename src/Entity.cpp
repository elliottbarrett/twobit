#include "Entity.h"
#include "Entities.h"

Entity::Entity(unsigned int id, std::string name, std::vector<std::string> params) :
    id(id), name(name)
{
    Entities::registerEntity(this, id, name);
}

Entity::~Entity()
{

}

void Entity::update(float dt)
{

}

std::string Entity::getName()
{
    return name;
}

unsigned int Entity::getId()
{
    return id;
}

std::string Entity::writeParameter(std::string name, int value)
{
    return name + " " + std::to_string(value) + "\n";
}

std::string Entity::writeParameter(std::string name, float value)
{
    return name + " " + std::to_string(value) + "\n";
}

std::string Entity::writeParameter(std::string name, std::string value)
{
    return name + " " + value + "\n";
}