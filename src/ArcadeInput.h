#ifndef ARCADE_INPUT_H
#define ARCADE_INPUT_H

enum JoyDirection
{
	NONE = 0b0000,
	UP = 0b0001,
	UP_RIGHT = 0b0101,
	RIGHT = 0b0100,
	DOWN_RIGHT = 0b0110,
	DOWN = 0b0010,
	DOWN_LEFT = 0b1010,
	LEFT = 0b1000,
	UP_LEFT = 0b1001
};

struct InputState
{
	JoyDirection direction;
	bool leftButton;
	bool rightButton;
};

class ArcadeInput
{
public:
	static InputState getPlayerOneState();
	static InputState getPlayerTwoState();
	static bool isWhiteButtonPressed();
};

#endif