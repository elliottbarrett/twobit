#include <SFML/Graphics.hpp>

#ifndef ANIMATION_H_INCLUDED
#define ANIMATION_H_INCLUDED

#include <vector>

class Animation
{
public:
    Animation();
    ~Animation();

    sf::IntRect getFrame(int frameIndex);
    float getTimePerFrame();
    int getFrameCount();

private:
    // Methods

    // Members
    float timePerFrame;
    std::vector<sf::IntRect> frames;
};

#endif