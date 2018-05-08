#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "AnimatedSprite.h"

class Player : public AnimatedSprite
{
public:
	Player();
	~Player();
	void update(float dt);
};

#endif