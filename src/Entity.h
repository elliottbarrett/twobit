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

    virtual void initParameters(std::vector<std::string> params);
    virtual void update(float dt);
    virtual void handleHorizontalWorldCollision(WorldCollision collision);
    virtual void handleVerticalWorldCollision(WorldCollision collision);
    virtual void handleEntityCollision(Entity* other) = 0;
    virtual std::string getEntityDescription() = 0;
    virtual EntityType getEntityType() = 0;
    std::string getName();
    unsigned int getId();
    void setVelocity(sf::Vector2f v);
    sf::Vector2f getVelocity();

    bool isCollidingWith(Entity* other);

    virtual sf::FloatRect getCollisionBounds();
    virtual void drawInspectorWidgets();
    
protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    std::string writeParameter(std::string name, int value);
    std::string writeParameter(std::string name, unsigned int value);
    std::string writeParameter(std::string name, float value);
    std::string writeParameter(std::string name, std::string value);
    std::string getCommonParameters();

    unsigned int id;
    std::string name;
    sf::Vector2f velocity;
    sf::RectangleShape collisionRect;
    std::vector<std::string> params;
};

#endif