#ifndef JUMPPAD_H_INCLUDED
#define JUMPPAD_H_INCLUDED

#include "Entity.h"

class JumpPad : public Entity
{
public:
    JumpPad(unsigned int id, std::string name, std::vector<std::string> params);
    ~JumpPad();

    void initParameters(std::vector<std::string> params);
    void update(float dt);
    std::string getEntityDescription();
    EntityType getEntityType();
    void handleEntityCollision(Entity* other);
    void drawInspectorWidgets();
    float getJumpModifier();

private:

    float jumpModifier;
};

#endif
