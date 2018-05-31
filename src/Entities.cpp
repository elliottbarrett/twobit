#include "Entities.h"
#include "Player.h"
#include "Door.h"
#include "Switch.h"
#include "TileMap.h"

#include <iostream>
#include <string>
#include <fstream>

std::map<std::string, Entity*> Entities::entityNameMap = std::map<std::string, Entity*>();
std::map<unsigned int, Entity*> Entities::entityIdMap = std::map<unsigned int, Entity*>();
std::vector<Entity*> Entities::entities = std::vector<Entity*>();
unsigned int Entities::maxId = 0;

void Entities::loadFromFile(std::string fileName)
{
    std::ifstream readStream(fileName);
    std::string line;
    bool isEntityDefinitionLine = true;
    unsigned int entityId;
    std::string entityType;
    std::string entityName;
    std::vector<std::string> parameterLines;

    while (std::getline(readStream, line))
    {
        if (line == "END") break;

        if (line == "")
        {
            initEntity(entityId, entityType, entityName, parameterLines);
            parameterLines.empty();
            isEntityDefinitionLine = true;
        }
        else if (isEntityDefinitionLine)
        {
            entityId = std::stoi(line.substr(0, line.find(" ")));
            line.erase(0, line.find(" ") + 1);
            entityType = line.substr(0, line.find(" "));
            line.erase(0, line.find(" ") + 1);
            entityName = line.substr(0, line.find(" "));

            // std::cout << "Entity " << entityName << " is a " << entityType << " (id: " << entityId << ")\n";
            isEntityDefinitionLine = false;
        }
        else
        {
            // std::cout << "Parameter line: " << line << "\n";
            parameterLines.push_back(line);
        }
    }
}


void Entities::initEntity(unsigned int id, std::string type, std::string name, std::vector<std::string> params)
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
    return entityIdMap[id];
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
        it->move(sf::Vector2f(0, vel.y * dt));
        it->handleVerticalWorldCollision(world.checkVerticalWorldCollisions(it));
    }
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