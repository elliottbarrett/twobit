#include "JumpPad.h"
#include "Animation.h"
#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"

JumpPad::JumpPad(unsigned int id, std::string name, std::vector<std::string> params) :
    Entity(id, name, params)
{

}

JumpPad::~JumpPad()
{

}

void JumpPad::initParameters(std::vector<std::string> params)
{
    Entity::initParameters(params);

    for (auto it : params)
    {
        auto key = it.substr(0, it.find(" "));
        auto value = it.substr(it.find(" ") + 1);
    
        if (key == "jumpModifier") jumpModifier = std::stof(value);
    }
}

EntityType JumpPad::getEntityType()
{
    return ET_JUMP_PAD;
}

float JumpPad::getJumpModifier()
{
    return jumpModifier;
}

std::string JumpPad::getEntityDescription()
{
    return std::to_string(id) + " JumpPad " + name + "\n"
        + getCommonParameters()
        + writeParameter("texture", "world_entities.png")
        + writeParameter("animation", currentAnimation->getName())
        + writeParameter("jumpModifier", jumpModifier);
}

void JumpPad::update(float dt)
{
    Entity::update(dt);
}

void JumpPad::handleEntityCollision(Entity *other)
{
    switch (other->getEntityType())
    {
    default:
        break;
    }
}

void JumpPad::drawInspectorWidgets()
{
    Entity::drawInspectorWidgets();

    ImGui::SliderFloat("Jump Modifier", &jumpModifier, 0, 200);
}
