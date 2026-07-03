#pragma once

struct s_vector2
{
	int	x;
	int	y;
};

enum class Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	NDF
};

enum class ActionType
{
	MoveCursor,
	Enter,
	Quit,
	NDF
};

struct s_Action
{
	ActionType type;
	Direction dir;
	s_vector2 target;
};

enum class 	GameState
{
	Playing,
	Finished,
	Quit
};
