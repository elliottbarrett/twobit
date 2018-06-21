#ifndef FOEBULLET_H_INCLUDED
#define FOEBULLET_H_INCLUDED

#include "Entity.h"

class FoeBullet : public Entity
{
public:
    FoeBullet(unsigned int id, std::string name, std::vector<std::string> params);
    ~FoeBullet();

    void update(float dt);
    std::string getEntityDescription();
    EntityType getEntityType();
    void handleEntityCollision(Entity* other);

    bool isAvailable();
    void fire(sf::Vector2f startPosition, sf::Vector2f velocity, float range);

private:
    void initParameters(std::vector<std::string> params);

    bool available;
    float range;
    float distanceTraveled;
};

#endif
