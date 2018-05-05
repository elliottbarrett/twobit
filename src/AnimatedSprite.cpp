#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite()
{

}

AnimatedSprite::AnimatedSprite(const AnimatedSprite &other)
{

}

AnimatedSprite::~AnimatedSprite()
{

}

virtual void AnimatedSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    // target.draw( , states);
}