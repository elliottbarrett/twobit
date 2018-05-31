#include "Entity.h"
#include "Entities.h"
#include "Settings.h"
#include "Animation.h"
#include "ResourceManager.h"

#include <string.h>
#include <stdio.h>
#include <iostream>
#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"

Entity::Entity(unsigned int id, std::string name, std::vector<std::string> params) :
    id(id), name(name), velocity(sf::Vector2f(0,0)), params(params)
{
    Entities::registerEntity(this, id, name);
    collisionRect.setFillColor(sf::Color::Transparent);
    collisionRect.setOutlineColor(sf::Color(255,0,255));
    collisionRect.setOutlineThickness(-1);
}

Entity::~Entity()
{

}

void Entity::update(float dt)
{
    AnimatedSprite::update(dt);

    if (Settings::instance().drawEntityCollisionBounds)
    {
        auto currentCollision = currentAnimation->getFrameCollision(currentFrame);
        collisionRect.setPosition(sf::Vector2f(currentCollision.left, currentCollision.top));
        collisionRect.setSize(sf::Vector2f(currentCollision.width, currentCollision.height));
    }
}

void Entity::initParameters(std::vector<std::string> params)
{
    sf::Vector2f pos;

    for (auto it : params)
    {
        auto key = it.substr(0, it.find(" "));
        auto value = it.substr(it.find(" ") + 1);

        if (key == "posX") pos.x = std::stof(value);
        else if (key == "posY") pos.y = std::stof(value);
        else if (key == "texture") setTexture(ResourceManager::getTexture(value));
        else if (key == "animation") playAnimation(value);
    }
    setPosition(pos);
}

std::string Entity::getCommonParameters()
{
    return writeParameter("posX", getPosition().x) + writeParameter("posY", getPosition().y);
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

std::string Entity::writeParameter(std::string name, unsigned int value)
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

void Entity::handleHorizontalWorldCollision(WorldCollision c) {}
void Entity::handleVerticalWorldCollision(WorldCollision c) {}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    AnimatedSprite::draw(target, states);

    if (Settings::instance().drawEntityCollisionBounds)
    {
        states.transform *= getTransform();
        target.draw(collisionRect, states);
    }
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

    auto bounds = getCollisionBounds();
    ImGui::Text("Bounds X: %f to %f", bounds.left, bounds.left + bounds.width);
    ImGui::Text("Bounds Y: %f to %f", bounds.top, bounds.top + bounds.height);

    setPosition(sf::Vector2f(position[0], position[1]));
}

bool Entity::isCollidingWith(Entity *other)
{
    return getCollisionBounds().intersects(other->getCollisionBounds());
}

sf::FloatRect Entity::getCollisionBounds()
{
    sf::Transform t = getTransform();
    auto bounds = t.transformRect(currentAnimation->getFrameCollision(currentFrame));
    return bounds;
}