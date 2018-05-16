#ifndef ENTITIES_H_INCLUDED
#define ENTITIES_H_INCLUDED

#include <map>
#include <string>

class Entity;

class Entities
{
public:
    static bool registerEntity(Entity *e, std::string name);
    static Entity* findByName(std::string name);

private:
    static std::map<std::string, Entity*> entityMap;
};

#endif