#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H

#include <SFML/Graphics.hpp>

class AnimatedSprite : public sf::Drawable, public sf::Transformable
{
	AnimatedSprite();
	AnimatedSprite(const AnimatedSprite &other);
	~AnimatedSprite();

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif