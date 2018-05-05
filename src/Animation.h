#include <SFML/Graphics.hpp>

#ifndef ANIMATION_H_INCLUDED
#define ANIMATION_H_INCLUDED

#include <vector>

class Animation
{
public:
	Animation();
	~Animation();
private:
	// Methods

	// Members
	float timePerFrame;
	std::vector<sf::IntRect> frames;
};

#endif