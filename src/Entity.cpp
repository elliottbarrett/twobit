#include "Entity.h"
#include "Entities.h"

#include <string.h>
#include <stdio.h>
#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"


Entity::Entity(unsigned int id, std::string name, std::vector<std::string> params) :
    id(id), name(name)
{
    Entities::registerEntity(this, id, name);
}

Entity::~Entity()
{

}

void Entity::update(float dt)
{

}

std::string Entity::getName()
{
    return name;
}

unsigned int Entity::getId()
{
    return id;
}

sf::Vector2f Entity::getVelocity()
{
    return velocity;
}

std::string Entity::writeParameter(std::string name, int value)
{
    return name + " " + std::to_string(value) + "\n";
}

std::string Entity::writeParameter(std::string name, float value)
{
    return name + " " + std::to_string(value) + "\n";
}

std::string Entity::writeParameter(std::string name, std::string value)
{
    return name + " " + value + "\n";
}

void Entity::drawInspectorWidgets()
{
    sf::Vector2f tmpPosition = getPosition();
    float position[2] = {tmpPosition.x, tmpPosition.y};
    float tmpVelocity[2] = {velocity.x, velocity.y};

    static char nameInputBuffer[40];
    strcpy(nameInputBuffer, name.c_str());
    if (ImGui::InputText("Name", nameInputBuffer, 40))
    {
        name = std::string(nameInputBuffer);
    }
    ImGui::DragFloat2("Position", position);
    ImGui::DragFloat2("Velocity", tmpVelocity);

    setPosition(sf::Vector2f(position[0], position[1]));
}