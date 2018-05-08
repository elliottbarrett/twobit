#include "Player.h"
#include "ArcadeInput.h"

Player::Player()
{
	AnimatedSprite();
}

Player::~Player()
{

}

void Player::update(float dt)
{
	AnimatedSprite::update(dt);

	InputState input = ArcadeInput::getPlayerOneState();
	// Vector2f 

	if (input.direction & JoyDirection::RIGHT)
	{
		move(1,0);
	}
	if (input.direction & JoyDirection::UP)
	{
		move(0,1);
	}
	if (input.direction & JoyDirection::LEFT)
	{
		move(-1,0);
	}
	if (input.direction & JoyDirection::DOWN)
	{
		move(0,-1);
	}

}