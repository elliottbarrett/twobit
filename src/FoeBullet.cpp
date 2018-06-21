#include "FoeBullet.h"
#include "Animation.h"
#include "sfmath.h"

FoeBullet::FoeBullet(unsigned int id, std::string name, std::vector<std::string> params) :
    Entity(id, name, params), available(true)
{

}

FoeBullet::~FoeBullet()
{

}

void FoeBullet::initParameters(std::vector<std::string> params)
{
    Entity::initParameters(params);
}

EntityType FoeBullet::getEntityType()
{
    return ET_FOE_BULLET;
}

std::string FoeBullet::getEntityDescription()
{
    return std::to_string(id) + " FoeBullet " + name + "\n"
        + getCommonParameters()
        + writeParameter("texture", "world_entities.png")
        + writeParameter("animation", currentAnimation->getName());
}

bool FoeBullet::isAvailable()
{
    return available;
}

void FoeBullet::update(float dt)
{
    Entity::update(dt);
    rotate(8);

    if (!available)
    {
        distanceTraveled += length(velocity * dt);

        if (distanceTraveled >= range)
        {
            available = true;
            setPosition(0,0);
        }
    }
}

void FoeBullet::fire(sf::Vector2f startPosition, sf::Vector2f velocity, float range)
{
    setPosition(startPosition);
    this->velocity = velocity;
    this->range = range;
    available = false;
    distanceTraveled = 0;
}

void FoeBullet::handleEntityCollision(Entity *other)
{
    switch (other->getEntityType())
    {
    default:
        break;
    }
}
