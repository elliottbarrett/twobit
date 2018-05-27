#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED

#include <string>

#include "AnimatedSprite.h"
#include "TileMap.h"
#include "EntityType.h"

class Entity : public AnimatedSprite
{
public:
    Entity(unsigned int id, std::string name, std::vector<std::string> params);
    ~Entity();

    virtual void update(float dt);
    virtual void handleHorizontalWorldCollision(WorldCollision collision) = 0;
    virtual void handleVerticalWorldCollision(WorldCollision collision) = 0;
    virtual std::string getEntityDescription() = 0;
    virtual EntityType getEntityType() = 0;
    std::string getName();
    unsigned int getId();
    sf::Vector2f getVelocity();

    virtual sf::FloatRect getCollisionBounds() = 0;

    virtual void drawInspectorWidgets();
    
protected:
    virtual void initParameters(std::vector<std::string> params) = 0;
    std::string writeParameter(std::string name, int value);
    std::string writeParameter(std::string name, float value);
    std::string writeParameter(std::string name, std::string value);

    unsigned int id;
    std::string name;
    sf::Vector2f velocity;
};

#endif