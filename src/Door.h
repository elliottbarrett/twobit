#ifndef DOOR_H_INCLUDED
#define DOOR_H_INCLUDED

#include "Entity.h"

class Door : public Entity
{
public:
    Door(unsigned int id, std::string name, std::vector<std::string> params);
    ~Door();

    void update(float dt);
    std::string getEntityDescription();
    EntityType getEntityType();
    sf::FloatRect getCollisionBounds();
    void handleEntityCollision();

private:
    void initParameters(std::vector<std::string> params);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif