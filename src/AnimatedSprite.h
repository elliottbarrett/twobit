#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H

#include <SFML/Graphics.hpp>

class Animation;

class AnimatedSprite : public sf::Drawable, public sf::Transformable
{
public:
	AnimatedSprite();
	AnimatedSprite(const AnimatedSprite &other);
	~AnimatedSprite();

	virtual void update(float dt);
	void setTexture(sf::Texture *texture);
	void playAnimation(Animation *animation);

protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void setFrame(int newFrame);

    sf::VertexArray vertices;
    sf::Texture *texture;
    Animation *currentAnimation;
    float timeInFrame;
    int currentFrame;
};

#endif