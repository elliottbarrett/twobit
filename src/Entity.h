#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED

#include <string>

#include "AnimatedSprite.h"

class Entity : public AnimatedSprite
{
public:
    Entity(std::string name);
    ~Entity();

    virtual void update(float dt);

private:
};

#endif