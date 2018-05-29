#include "Animation.h"

#include <iostream>

Animation::Animation()
{

}

void Animation::setTimePerFrame(float t)
{
    timePerFrame = t;
}

void Animation::setOrigin(sf::Vector2f o)
{
    origin = o;
}

void Animation::addFrame(sf::IntRect rect, sf::FloatRect collision)
{
    frames.push_back(rect);
    collisions.push_back(collision);
}

sf::Vector2f Animation::getOrigin()
{
    return origin;
}

sf::IntRect Animation::getFrame(int frameIndex)
{
    return frames[frameIndex];
}

sf::FloatRect Animation::getFrameCollision(int frameIndex)
{
    return collisions[frameIndex];
}

int Animation::getFrameCount()
{
    return frames.size();
}

float Animation::getTimePerFrame()
{
    return timePerFrame;
}