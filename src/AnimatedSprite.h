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
    void playAnimation(std::string name, int startingFrame = 0, bool interruptable = true);
    void playAnimationLooped(std::string name);

protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void setFrame(int newFrame);
    void faceLeft();
    void faceRight();
    void flashForSeconds(float t, float flashPeriod);

    sf::VertexArray vertices;
    sf::Texture *texture;
    Animation *currentAnimation;
    float timeInFrame;
    int currentFrame;
    bool loopAnimation;
    bool currentAnimationIsInterruptable;

    float flashTime;
    float flashPeriod;
    float flashElapsed;
};

#endif