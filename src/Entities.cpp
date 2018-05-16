#include "Entities.h"
#include "Player.h"

#include <iostream>
#include <string>
#include <fstream>

std::map<std::string, Entity*> Entities::entityNameMap = std::map<std::string, Entity*>();
std::map<unsigned int, Entity*> Entities::entityIdMap = std::map<unsigned int, Entity*>();
std::vector<Entity*> Entities::entities = std::vector<Entity*>();

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
        auto ent = new Player(id, name, params);
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

Entity* Entities::findByName(std::string name)
{
    return entityNameMap[name];
}

int Entities::getCount()
{
    return entities.size();
}

void Entities::update(float dt)
{
    for (auto it : entities)
    {
        it->update(dt);
    }
}

void Entities::draw(sf::RenderWindow &window)
{
    for (auto it : entities)
    {
        window.draw(*it);
    }
}