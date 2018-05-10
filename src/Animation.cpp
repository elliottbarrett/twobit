#include "Animation.h"

Animation::Animation()
{
    frames = 
    { 
        sf::IntRect(0,0,16,16), sf::IntRect(0,16,16,16), sf::IntRect(0,32,16,16), sf::IntRect(0,48,16,16) 
    };
    timePerFrame = 2;
}

sf::IntRect Animation::getFrame(int frameIndex)
{
    sf::IntRect rect;
    rect = frames[frameIndex];
    return rect;
}

int Animation::getFrameCount()
{
    return frames.size();
}

float Animation::getTimePerFrame()
{
    return timePerFrame;
}