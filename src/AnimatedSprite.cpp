#include "AnimatedSprite.h"
#include "Animation.h"
#include "ResourceManager.h"

#include <iostream>

AnimatedSprite::AnimatedSprite() :
    timeInFrame(0), loopAnimation(true)
{
    vertices.setPrimitiveType(sf::Quads);
    vertices.resize(4);
}

AnimatedSprite::~AnimatedSprite()
{

}

void AnimatedSprite::update(float dt)
{
    float timePerFrame = currentAnimation->getTimePerFrame();
    int frameCount = currentAnimation->getFrameCount();

    timeInFrame += dt;

    if (timeInFrame >= timePerFrame)
    {
        timeInFrame -= timePerFrame;

        if (!loopAnimation && currentFrame == frameCount -1) return;

        setFrame((currentFrame + 1) % frameCount); // TODO: Update this for animation "types"
    }
}

void AnimatedSprite::setTexture(sf::Texture *newTexture)
{
    texture = newTexture;
}

void AnimatedSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    states.texture = texture;
    target.draw(vertices, states);
}

void AnimatedSprite::setFrame(int newFrame)
{
    currentFrame = newFrame;

    auto frameBounds = currentAnimation->getFrame(currentFrame);

    vertices[0].position = sf::Vector2f(0,0);
    vertices[1].position = sf::Vector2f(0,frameBounds.height);
    vertices[2].position = sf::Vector2f(frameBounds.width, frameBounds.height);
    vertices[3].position = sf::Vector2f(frameBounds.width,0);

    float left = frameBounds.left;
    float right = frameBounds.left + frameBounds.width;
    float top = frameBounds.top;
    float bottom = frameBounds.top + frameBounds.height;

    vertices[0].texCoords = sf::Vector2f(left, bottom);
    vertices[1].texCoords = sf::Vector2f(left, top);
    vertices[2].texCoords = sf::Vector2f(right, top);
    vertices[3].texCoords = sf::Vector2f(right, bottom);
}

void AnimatedSprite::playAnimation(std::string name, int startingFrame)
{
    if (currentAnimation == ResourceManager::getAnimation(name)) return;

    loopAnimation = false;

    currentAnimation = ResourceManager::getAnimation(name);
    timeInFrame = 0;
    setFrame(startingFrame);
    setOrigin(currentAnimation->getOrigin());
}

void AnimatedSprite::playAnimationLooped(std::string name)
{
    if (currentAnimation == ResourceManager::getAnimation(name)) return;

    loopAnimation = true;

    currentAnimation = ResourceManager::getAnimation(name);
    timeInFrame = 0;
    setFrame(0);
    setOrigin(currentAnimation->getOrigin());
}