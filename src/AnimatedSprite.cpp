#include "AnimatedSprite.h"
#include "Animation.h"

#include <iostream>

AnimatedSprite::AnimatedSprite()
{
	vertices.setPrimitiveType(sf::Quads);
	vertices.resize(4);

	// XXX
	currentAnimation = new Animation();
	// currentAnimation->
	//
	setFrame(0);
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
		std::cout << "changing frame from " << currentFrame << std::endl;
		timeInFrame -= timePerFrame;
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

	vertices[0].texCoords = sf::Vector2f(left, top);
	vertices[1].texCoords = sf::Vector2f(left, bottom);
	vertices[2].texCoords = sf::Vector2f(right, bottom);
	vertices[3].texCoords = sf::Vector2f(right, top);
}

void AnimatedSprite::playAnimation(Animation *animation)
{
	currentAnimation = animation;
	currentFrame = 0;
	timeInFrame = 0;
}