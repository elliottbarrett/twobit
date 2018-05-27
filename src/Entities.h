#ifndef ENTITIES_H_INCLUDED
#define ENTITIES_H_INCLUDED

#include <map>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

class TileMap;
class Entity;

class Entities
{
public:
    static void loadFromFile(std::string fileName);
    static void writeFile(std::string fileName);
    static bool registerEntity(Entity *e, unsigned int id, std::string name);
    static int getCount();
    static std::vector<Entity*> getEntities();

    static void update(float dt, TileMap &world);
    static void handleWorldCollisions(TileMap &world);
    static void draw(sf::RenderWindow &window);

    static Entity* getByName(std::string name);
    static Entity* getById(unsigned int id);
    static unsigned int getMaxId();

    static void deleteById();

private:
    static void initEntity(unsigned int id, std::string type, std::string name, std::vector<std::string> params);

    static std::vector<Entity*> entities;
    static std::map<unsigned int, Entity*> entityIdMap;
    static std::map<std::string, Entity*> entityNameMap;
    static unsigned int maxId;
};

#endif