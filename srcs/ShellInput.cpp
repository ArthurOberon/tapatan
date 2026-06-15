#include "ShellInput.hpp"

ShellInput::ShellInput(/* args */) {}

ShellInput::~ShellInput() {}

const s_Action	ShellInput::poll() const
{
	int	key = getch();

	switch (key)
	{
	case KEY_UP:
		return (s_Action{ActionType::MoveCursor, Direction::UP, {-1, -1}});
	case KEY_DOWN:
		return (s_Action{ActionType::MoveCursor, Direction::DOWN, {-1, -1}});
	case KEY_LEFT:
		return (s_Action{ActionType::MoveCursor, Direction::LEFT, {-1, -1}});
	case KEY_RIGHT:
		return (s_Action{ActionType::MoveCursor, Direction::RIGHT, {-1, -1}});

	case ' ' :
	case '\n' :
		return (s_Action{ActionType::Enter, Direction::NDF, {-1, -1}});

	case 'q' :
	case 'Q' :
		return (s_Action{ActionType::Quit, Direction::NDF, {-1, -1}});
	}
	return (s_Action{ActionType::NDF, Direction::NDF, {-1, -1}});
}
