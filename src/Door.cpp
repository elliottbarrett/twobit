#include "Door.h"
#include "ResourceManager.h"

Door::Door(unsigned int id, std::string name, std::vector<std::string> params) :
    Entity(id, name, params)
{

}

Door::~Door()
{

}

void Door::initParameters(std::vector<std::string> params)
{
    sf::Vector2f pos;
    for (auto it : params)
    {
        auto key = it.substr(0, it.find(" "));
        auto value = it.substr(it.find(" ") + 1);

        if (key == "posX") pos.x = std::stof(value);
        else if (key == "posY") pos.y = std::stof(value);
        else if (key == "texture") setTexture(ResourceManager::getTexture(value));
    }
}

EntityType Door::getEntityType()
{
    return ET_DOOR;
}

std::string Door::getEntityDescription()
{
    // TODO
    return "";
}

void Door::update(float dt)
{
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

sf::FloatRect Door::getCollisionBounds()
{
    auto transform = getTransform();
    return transform.transformRect(sf::FloatRect(0,0,8,16));
}

void Door::handleHorizontalWorldCollision(WorldCollision collision) {}
void Door::handleVerticalWorldCollision(WorldCollision collision) {}