#include "ShellInput.hpp"

ShellInput::ShellInput(/* args */) {}

ShellInput::~ShellInput() {}

const s_Action	ShellInput::poll() const
{
	int	key = getch();

	switch (key)
	{
	case KEY_UP:
		return (s_Action{ActionType::MoveCursor, Direction::UP});
	case KEY_DOWN:
		return (s_Action{ActionType::MoveCursor, Direction::DOWN});
	case KEY_LEFT:
		return (s_Action{ActionType::MoveCursor, Direction::LEFT});
	case KEY_RIGHT:
		return (s_Action{ActionType::MoveCursor, Direction::RIGHT});

	case ' ':
	case '\n' :
		return (s_Action{ActionType::Enter, Direction::NDF});

	case 'q' :
	case 'Q' :
		return (s_Action{ActionType::Quit, Direction::NDF});
	}
	return (s_Action{ActionType::NDF, Direction::NDF});
}
