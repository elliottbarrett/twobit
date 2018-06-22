#ifndef FOE_H_INCLUDED
#define FOE_H_INCLUDED

#include "Entity.h"

/* 
Some things that a foe might be concerned with...

-patrolling between points
-responding to line-of-sight
-switching between different behaviours
*/

class Player;
class FoeBullet;

class Foe : public Entity
{
public:
    Foe(unsigned int id, std::string name, std::vector<std::string> params);
    ~Foe();

    void initParameters(std::vector<std::string> params);
    void update(float dt);
    std::string getEntityDescription();
    EntityType getEntityType();
    void handleEntityCollision(Entity* other);

private:
    std::vector<sf::Vector2f> patrolPoints;
    std::vector<Player*> playerRefs;
    std::vector<FoeBullet*> bulletRefs;

    float attackCooldown;
    float attackCooldownElapsed;
    // int current
};

#endif
