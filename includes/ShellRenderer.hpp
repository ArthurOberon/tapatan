#pragma once

#include <ncurses.h>
#include "Game_.hpp"

class ShellRenderer
{
private:
	/* data */
public:
	ShellRenderer(/* args */);
	~ShellRenderer();

	void	draw(const Game_ & game);
	void	drawWinner(const int player) const;
};
