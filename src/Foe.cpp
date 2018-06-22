#include "Foe.h"
#include "FoeBullet.h"
#include "Player.h"
#include "Entities.h"
#include "sfmath.h"

Foe::Foe(unsigned int id, std::string name, std::vector<std::string> params) :
    Entity(id, name, params)
{

}

Foe::~Foe()
{

}

void Foe::initParameters(std::vector<std::string> params)
{
    Entity::initParameters(params);

    for (auto it : params)
    {
        auto key = it.substr(0, it.find(" "));
        auto value = it.substr(it.find(" ") + 1);

        if (key == "attackCooldown") attackCooldown = std::stof(value);
    }

    playerRefs.push_back((Player*)Entities::getById(1));
    playerRefs.push_back((Player*)Entities::getById(2));

    auto bullets = Entities::getByType(ET_FOE_BULLET);

    for (auto it : *bullets)
    {
        bulletRefs.push_back((FoeBullet*)it);
    }
}

EntityType Foe::getEntityType()
{
    return ET_FOE;
}

std::string Foe::getEntityDescription()
{
    return std::to_string(id) + " Foe " + name + "\n"
        + getCommonParameters()
        + writeParameter("texture", "world_entities.png")
        + writeParameter("animation", "foe_idle")
        + writeParameter("attackCooldown", attackCooldown);
}

void Foe::update(float dt)
{
    Entity::update(dt);

    attackCooldownElapsed += dt;

    float minDistance = 100000;
    float attackRange = 60;
    sf::Vector2f closestPlayerDirection;
    

    for (auto it : playerRefs)
    {
        auto playerPosition = it->getPosition();
        float playerDistance = distance(getPosition(), playerPosition);

        if (playerDistance < minDistance)
        {
            minDistance = playerDistance;
            closestPlayerDirection = normalize(playerPosition - getPosition()); 
        }
    }

    if (closestPlayerDirection.x < 0)
    {
        faceLeft();
    }
    else
    {
        faceRight();
    }
    
    if (minDistance <= attackRange && attackCooldownElapsed >= attackCooldown)
    {
        // TODO --- better solution for this (store pool of all potential bullets, find first available)
        //      This solution should also take into account an attack cooldown period.
        float attackSpeed = 55;


        FoeBullet* bullet = nullptr;

        for (auto it : bulletRefs)
        {
            if (it->isAvailable())
            {
                bullet = it;
            }
        }


        if (bullet != nullptr)
        {
            attackCooldownElapsed = 0;
            auto bulletStartOffset = sf::Vector2f(8 * getScale().x, 14);
            auto bulletStartPosition = sf::Vector2f(getPosition() + bulletStartOffset);
            bullet->fire(bulletStartPosition, closestPlayerDirection * attackSpeed, 100);
        }
    }
}

void Foe::handleEntityCollision(Entity *other)
{
    switch (other->getEntityType())
    {
    default:
        break;
    }
}
