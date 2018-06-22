#include "Entities.h"
#include "Player.h"
#include "Door.h"
#include "Foe.h"
#include "FoeBullet.h"
#include "NPC.h"
#include "Switch.h"
#include "Platform.h"
#include "TileMap.h"
#include "Ball.h"
#include "JumpPad.h"

#include <iostream>
#include <string>
#include <fstream>

std::map<std::string, Entity*> Entities::entityNameMap;
std::map<unsigned int, Entity*> Entities::entityIdMap;
std::vector<Entity*> Entities::entities;;
std::map<EntityType, std::vector<Entity*>*> Entities::entityTypeMap;
unsigned int Entities::maxId = 0;

void Entities::loadFromFile(std::string fileName)
{
    std::ifstream instantiationReadStream(fileName);
    std::string line;
    bool isEntityDefinitionLine = true;
    unsigned int entityId;
    std::string entityType;
    std::string entityName;
    std::vector<std::string> parameterLines;

    while (std::getline(instantiationReadStream, line))
    {
        if (line == "END") break;

        if (line == "")
        {
            instantiateEntity(entityId, entityType, entityName);
            parameterLines.clear();
            isEntityDefinitionLine = true;
        }
        else if (isEntityDefinitionLine)
        {
            entityId = std::stoi(line.substr(0, line.find(" ")));
            line.erase(0, line.find(" ") + 1);
            entityType = line.substr(0, line.find(" "));
            line.erase(0, line.find(" ") + 1);
            entityName = line.substr(0, line.find(" "));

            isEntityDefinitionLine = false;
        }
        else
        {
            parameterLines.push_back(line);
        }
    }
    instantiationReadStream.close();

    isEntityDefinitionLine = true;
    std::ifstream initializationReadStream(fileName);
    while (std::getline(initializationReadStream, line))
    {
        if (line == "END") break;

        if (line == "")
        {
            auto currentEntity = getById(entityId);

            if (currentEntity != nullptr)
            {
                currentEntity->initParameters(parameterLines);
            }

            parameterLines.clear();
            isEntityDefinitionLine = true;
        }
        else if (isEntityDefinitionLine)
        {
            entityId = std::stoi(line.substr(0, line.find(" ")));
            line.erase(0, line.find(" ") + 1);
            entityType = line.substr(0, line.find(" "));
            line.erase(0, line.find(" ") + 1);
            entityName = line.substr(0, line.find(" "));

            isEntityDefinitionLine = false;
        }
        else
        {
            // std::cout << "Parameter line: " << line << "\n";
            parameterLines.push_back(line);
        }
    }
    initializationReadStream.close();
}

unsigned int Entities::getMaxId()
{
    return maxId;
}

void Entities::instantiateEntity(unsigned int id, std::string type, std::string name, std::vector<std::string> params)
{
    if (type == "Player")
    {
        new Player(id, name, params);
    }
    else if (type == "Door")
    {
        new Door(id, name, params);
    }
    else if (type == "Switch")
    {
        new Switch(id, name, params);
    }
    else if (type == "NPC")
    {
        new NPC(id, name, params);
    }
    else if (type == "Platform")
    {
        new Platform(id, name, params);
    }
    else if (type == "Ball")
    {
        new Ball(id, name, params);
    }
    else if (type == "Foe")
    {
        new Foe(id, name, params);
    }
    else if (type == "FoeBullet")
    {
        new FoeBullet(id, name, params);
    }
    else if (type == "JumpPad")
    {
        new JumpPad(id, name, params);
    }
    else
    {
        std::cout << "Unrecognized entity " << name << " of type " << type << std::endl;
    }
}

void Entities::writeFile(std::string fileName)
{
    std::ofstream outputStream;
    outputStream.open(fileName);

    for (auto entity : entities)
    {
        outputStream << entity->getEntityDescription() << "\n";
    }

    outputStream << "END";
    outputStream.close();
}

bool Entities::registerEntity(Entity *e, unsigned int id, std::string name)
{
    auto existingEntity = entityIdMap[id];
    
    if (id > maxId)
    {
        maxId = id;
    }

    if (!existingEntity)
    {
        entityNameMap[name] = e;
        entityIdMap[id] = e;
        entities.push_back(e);
        return true;
    }
    else
    {
        std::cout << "skipping " << name << " " << id << "\n";
        return false;
    }
}

std::vector<Entity*> Entities::getEntities()
{
    return entities;
}

Entity* Entities::getByName(std::string name)
{
    return entityNameMap[name];
}

Entity* Entities::getById(unsigned int id)
{
    if (entityIdMap.find(id) == entityIdMap.end())
    {
        std::cout << "Could not find entity with id " << id << "\n";
    }
    return entityIdMap[id];
}

std::vector<Entity*>* Entities::getByType(EntityType type)
{
    if (entityTypeMap.find(type) != entityTypeMap.end())
    {
        return entityTypeMap[type];
    }

    auto entitiesForType = new std::vector<Entity*>();
    for (auto it : entities)
    {
        if (it->getEntityType() == type)
        {
            entitiesForType->push_back(it);
        }
    }
    entityTypeMap[type] = entitiesForType;

    return entitiesForType;
}

int Entities::getCount()
{
    return entities.size();
}

void Entities::update(float dt, TileMap &world)
{
    for (auto it : entities)
    {
        it->update(dt);

        auto vel = it->getVelocity();
        it->move(sf::Vector2f(vel.x * dt, 0));
        it->handleHorizontalWorldCollision(world.checkHorizontalWorldCollisions(it));
    }

    handleEntityCollisions();

    for (auto it : entities)
    {
        auto vel = it->getVelocity();
        it->move(sf::Vector2f(0, vel.y * dt));
        it->handleVerticalWorldCollision(world.checkVerticalWorldCollisions(it));
    }

    handleEntityCollisions();    
}

void Entities::handleEntityCollisions()
{
    std::vector<Entity*> lowCollider;
    std::vector<Entity*> highCollider;

    for (unsigned int i=0; i < entities.size() - 1; i++)
    {
        Entity* lowEntity = entities[i];

        for (unsigned int j=i+1; j < entities.size(); j++)
        {
            Entity* highEntity = entities[j];

            if (lowEntity->isCollidingWith(highEntity))
            {
                lowEntity->handleEntityCollision(highEntity);
                highEntity->handleEntityCollision(lowEntity);
            }
        }
    }    
}

void Entities::draw(sf::RenderWindow &window)
{
    for (auto it : entities)
    {
        window.draw(*it);
    }
}