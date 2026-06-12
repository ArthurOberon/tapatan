#pragma once

#include "ShellRenderer.hpp"

// enum class ActionType
// {
// 	MoveCursor,
// 	Enter,
// 	Quit
// };

// struct s_Action
// {
// 	ActionType type;
// 	Direction dir;
// };

class ShellInput
{
private:
	/* data */
public:
	ShellInput(/* args */);
	~ShellInput();

	const s_Action	poll() const;
};
