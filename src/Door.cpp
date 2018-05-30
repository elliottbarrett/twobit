#include "Door.h"
#include "ResourceManager.h"

Door::Door(unsigned int id, std::string name, std::vector<std::string> params) :
    Entity(id, name, params)
{
    initParameters(params);
}

Door::~Door()
{

}

void Door::initParameters(std::vector<std::string> params)
{
    Entity::initParameters(params);
}

EntityType Door::getEntityType()
{
    return ET_DOOR;
}

std::string Door::getEntityDescription()
{
    return std::to_string(id) + " Door " + name + "\n"
        + writeParameter("posX", getPosition().x)
        + writeParameter("posY", getPosition().y)
        + writeParameter("texture", "door.png")
        + writeParameter("animation", "door_closed");
}

void Door::update(float dt)
{
    Entity::update(dt);
    // TODO
}

void Door::handleEntityCollision(Entity *other)
{
    switch (other->getEntityType())
    {
        case ET_PROJECTILE:

        default:
            break;
    }
}
