#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED

#include <string>

#include "AnimatedSprite.h"

class Entity : public AnimatedSprite
{
public:
    Entity(unsigned int id, std::string name, std::vector<std::string> params);
    ~Entity();

    virtual void update(float dt);
    virtual std::string getEntityDescription() = 0;
    std::string getName();
    unsigned int getId();
    sf::Vector2f getVelocity();

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