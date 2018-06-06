#include "Player.h"
#include "ArcadeInput.h"
#include "Settings.h"
#include "ResourceManager.h"
#include "TileMap.h"
#include "Animation.h"
#include "sfmath.h"
#include <math.h>
#include <iostream>


Player::Player(unsigned int id, std::string name, std::vector<std::string> params) :
    Entity(id, name, params),
    currentItem(PI_NONE),
    isOnGround(true), wasOnGround(true),
    isAtCeiling(false), wasAtCeiling(false),
    isPushingLeftWall(false), wasPushingLeftWall(false),
    isPushingRightWall(false), wasPushingRightWall(false),
    framesSinceJump(0)
{
    initParameters(params);

    playAnimation("player_idle");
}

Player::~Player()
{
}

void Player::initParameters(std::vector<std::string> params)
{
    Entity::initParameters(params);

    for (auto it : params)
    {
        auto key = it.substr(0, it.find(" "));
        auto value = it.substr(it.find(" ") + 1);

        if (key == "playerNum") playerNumber = std::stoi(value);
    }
}

EntityType Player::getEntityType()
{
    return ET_PLAYER;
}

std::string Player::getEntityDescription()
{
    return std::to_string(id) + " Player " + name + "\n"
        + getCommonParameters()
        + writeParameter("playerNum", playerNumber)
        + writeParameter("texture", "player.png")
        + writeParameter("animation", "player_idle");
}


void Player::update(float dt)
{
    Entity::update(dt);

    framesSinceJump++;

    InputState input = playerNumber == 1 ? ArcadeInput::getPlayerOneState() : ArcadeInput::getPlayerTwoState();
    auto settings = &Settings::instance();

    if (input.direction & JoyDirection::LEFT)
    {
        playAnimationLooped("player_walk");
        velocity.x = -1 * settings->walkSpeed;
        setScale(-1,1);
    }
    else if (input.direction & JoyDirection::RIGHT)
    {
        playAnimationLooped("player_walk");
        velocity.x = settings->walkSpeed;
        setScale(1,1);
    }
    else if (!isOnGround)
    {
        velocity.x = velocity.x - 0.05f * velocity.x;
    }
    else
    {
        velocity.x = 0;
    }


    if (abs(velocity.x) <= 10 && currentAnimation->getName() != "player_stick") 
    {
        playAnimation("player_idle");
    }

    if (input.direction & JoyDirection::UP)
    {
        if (isOnGround)
        {
            isOnGround = false;
            velocity.y = settings->jumpSpeed;
            framesSinceJump = 0;
        }
    }
    if (input.direction & JoyDirection::DOWN)
    {
        // move(0,-1);
    }

    if (!isOnGround)
    {
        velocity.y += settings->gravity * dt;
        velocity.y = clamp(velocity.y, -200, 300);
    }

    if (input.rightButton) // this is z
    {
        if (isOnGround)
        {
            isOnGround = false;
            velocity.y = settings->jumpSpeed;
            framesSinceJump = 0;
        }
    }

    if (input.leftButton)
    {
        tryUseCurrentItem();
    }

    updatePhysics();
}

PlayerItem Player::getCurrentItem()
{
    // XX
    return playerNumber == 1 ? PI_STICK : PI_BALL;
    return currentItem;
}

void Player::tryUseCurrentItem()
{
    switch (currentItem)
    {
    case PI_STICK:
        break;
    case PI_BALL:

        break;
    default:
        playAnimation("player_stick", 0, false);
        break;
    }
}

void Player::switchItem()
{
    
}

void Player::updatePhysics()
{
    wasOnGround = isOnGround;
    wasAtCeiling = isAtCeiling;
    wasPushingLeftWall = isPushingLeftWall;
    wasPushingRightWall = isPushingRightWall; 
}

void Player::handleHorizontalWorldCollision(WorldCollision collision)
{
    if (collision.hitLeft)
    {
        velocity.x = 0;
        move(-(collision.xIntersectionDistance - 0.01), 0);
    }
    else if (collision.hitRight)
    {
        velocity.x = 0;
        move(-(collision.xIntersectionDistance + 0.01), 0);
    }
}

void Player::handleVerticalWorldCollision(WorldCollision collision)
{
    if (collision.hitBottom && collision.yIntersectionDistance > 0)
    {
        isOnGround = true;
        velocity.y = 0;
        move(0, 16 - collision.yIntersectionDistance);
    }
    else if (collision.hitTop && collision.yIntersectionDistance > 0)
    {
        isAtCeiling = true;
        move(0, -(collision.yIntersectionDistance + 0.01));
        velocity.y *= 0.3;
    }
    else
    {
        isOnGround = false;
    }
}

void Player::handleEntityCollision(Entity *other)
{
    auto myBounds = getCollisionBounds();
    auto myPosition = getPosition();
    auto otherBounds = other->getCollisionBounds();

    switch (other->getEntityType())
    {
    case ET_DOOR:
        if (velocity.x > 0)
        {
            move(-(myBounds.left + myBounds.width - otherBounds.left), 0);
        }
        else
        {
            move(otherBounds.left + otherBounds.width - myBounds.left, 0);
        }
        break;
    case ET_PLATFORM:

        if (otherBounds.contains(myPosition) && framesSinceJump > 4)
        {
            isOnGround = true;
            velocity = sf::Vector2f(velocity.x, other->getVelocity().y);
            // setPosition(myPosition.x, otherBounds.top + otherBounds.height);
        }
    default:
        break;
    }
}

void Player::drawInspectorWidgets()
{
    Entity::drawInspectorWidgets();
}