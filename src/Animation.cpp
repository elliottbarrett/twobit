#include "Animation.h"

#include <iostream>

Animation::Animation()
{

}

void Animation::setName(std::string name)
{
    this->name = name;
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

std::string Animation::getName()
{
    return name;
}

sf::IntRect Animation::getFrame(int frameIndex)
{
    if (frameIndex > frames.size())
    {
        std::cout << "Animation: Requested frame " << frameIndex << " from animation of size " << frames.size() << "\n";
        return sf::IntRect(0,0,0,0);
    }
    return frames[frameIndex];
}

sf::FloatRect Animation::getFrameCollision(int frameIndex)
{
    if (frameIndex > collisions.size())
    {
        std::cout << "Animation: Requested collision " << frameIndex << " from animation of size " << collisions.size() << "\n";
        return sf::FloatRect(0,0,0,0);
    }
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