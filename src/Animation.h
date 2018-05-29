#include <SFML/Graphics.hpp>

#ifndef ANIMATION_H_INCLUDED
#define ANIMATION_H_INCLUDED

#include <vector>

class Animation
{
public:
    Animation();
    ~Animation();

    void setTimePerFrame(float t);
    void setOrigin(sf::Vector2f o);
    void addFrame(sf::IntRect rect, sf::FloatRect collision);

    sf::IntRect getFrame(int frameIndex);
    sf::FloatRect getFrameCollision(int frameIndex);
    float getTimePerFrame();
    sf::Vector2f getOrigin();
    int getFrameCount();

private:
    // Methods

    // Members
    float timePerFrame;
    sf::Vector2f origin;
    std::vector<sf::IntRect> frames;
    std::vector<sf::FloatRect> collisions;
};

#endif