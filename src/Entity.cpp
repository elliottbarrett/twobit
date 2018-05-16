#include "Entity.h"
#include "Entities.h"

Entity::Entity(std::string name)
{
    Entities::registerEntity(this, name);
}

Entity::~Entity()
{

}

void Entity::update(float dt)
{

}