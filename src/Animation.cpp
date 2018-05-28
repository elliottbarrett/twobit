#include "Animation.h"

Animation::Animation()
{
    frames = 
    { 
        sf::IntRect(0,0,16,24), sf::IntRect(16,0,16,24), sf::IntRect(32,0,16,24), sf::IntRect(48,0,16,24) 
    };
    timePerFrame = 0.2;
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