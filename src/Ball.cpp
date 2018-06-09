#include "Ball.h"
#include "Settings.h"

Ball::Ball(unsigned int id, std::string name, std::vector<std::string> params)
    : Entity(id, name, params), isActive(true)
{

}

Ball::~Ball()
{

}

void Ball::initParameters(std::vector<std::string> params)
{
    Entity::initParameters(params);
}

void Ball::update(float dt)
{
    Entity::update(dt);

    auto settings = &Settings::instance();

    if (isActive)
    {
        // velocity.x
        velocity.y += settings->gravity * dt;
    }
}

std::string Ball::getEntityDescription()
{
    return std::to_string(id) + " Ball " + name + "\n"
        + getCommonParameters()
        + writeParameter("texture", "world_entities.png")
        + writeParameter("animation", "ball");
}

EntityType Ball::getEntityType()
{
    return ET_BALL;
}

void Ball::handleHorizontalWorldCollision(WorldCollision collision)
{
    if (collision.hitLeft)
    {
        move(-(collision.xIntersectionDistance - 0.01), 0);
        velocity.x *= -0.5;
        if (std::abs(velocity.x) < 10) velocity.x = 0;
    }
    else if (collision.hitRight)
    {
        move(-(collision.xIntersectionDistance + 0.01), 0);    
        velocity.x *= -0.5;
        if (std::abs(velocity.x) < 10) velocity.x = 0;
    }

}

void Ball::handleVerticalWorldCollision(WorldCollision collision)
{
    if (collision.hitBottom && collision.yIntersectionDistance > 0)
    {
        move(0, 16 - collision.yIntersectionDistance);
        velocity.y *= -0.5;
        velocity.x *= 0.7;
        if (std::abs(velocity.y) < 10) velocity.y = 0;
    }
    else if (collision.hitTop && collision.yIntersectionDistance > 0)
    {
        move(0, -(collision.yIntersectionDistance + 0.01));
        velocity.y *= -0.5;
        velocity.x *= 0.7;
        if (std::abs(velocity.y) < 10) velocity.y = 0;
    }
}

void Ball::handleEntityCollision(Entity* other)
{
    auto myBounds = getCollisionBounds();
    auto otherBounds = other->getCollisionBounds();

    switch (other->getEntityType())
    {
    case ET_DOOR:
        if (velocity.x > 0)
        {
            move(-(myBounds.left + myBounds.width - otherBounds.left), 0);
            velocity.x *= -0.7;
        }
        else
        {
            move(otherBounds.left + otherBounds.width - myBounds.left, 0);
            velocity.x *= -0.7;
        }
        break;
    default:
        break;
    }
}