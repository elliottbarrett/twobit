#ifndef NPC_H_INCLUDED
#define NPC_H_INCLUDED

#include "Entity.h"

class NPC : public Entity
{
public:
    NPC(unsigned int id, std::string name, std::vector<std::string> params);
    ~NPC();

    void update(float dt);
    std::string getEntityDescription();
    EntityType getEntityType();
    void handleEntityCollision(Entity* other);

private:
    void initParameters(std::vector<std::string> params);

};

#endif