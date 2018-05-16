#include "Entities.h"

#include <string>

std::map<std::string, Entity*> Entities::entityMap = std::map<std::string, Entity*>();

bool Entities::registerEntity(Entity *e, std::string name)
{
    auto it = entityMap.find(name);
    
    if (it == entityMap.end())
    {
        entityMap[name] = e;
        return true;
    }
    else
    {
        return false;
    }
}

Entity* Entities::findByName(std::string name)
{
    return entityMap[name];
}