#pragma once

#include <ncurses.h>
#include "Game.hpp"

class ShellRenderer
{
private:
	/* data */
public:
	ShellRenderer(/* args */);
	~ShellRenderer();

	void	draw(const Game & game);
	void	drawWinner(const int player) const;
};
