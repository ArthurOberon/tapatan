#include "ShellRenderer.hpp"

ShellRenderer::ShellRenderer(/* args */)
{
	initscr();
	keypad(stdscr, TRUE);
}

ShellRenderer::~ShellRenderer()
{
	endwin();
}


void	ShellRenderer::draw(const Game_ & game)
{
	if (game.getGameState() == GameState::Winner)
	{
		this->drawWinner(game.getPlayerTurn());
		return ;
	}

	s_vector2	cursor(game.getCursor());

	clear();
	for (int y = 0; y < 3; ++y)
	{
		for (int x = 0; x < 3; ++x)
		{
			if (x == cursor.x && y == cursor.y)
				attron(A_REVERSE);

			printw("[%c] ", game.getGridCell({y, x}));

			if (x == cursor.x && y == cursor.y)
				attroff(A_REVERSE);
		}
		printw("\n");
	}
	printw("turn : player %d\n", game.getPlayerTurn());
	// printw("x : %d\n", cursor.x);
	// printw("y : %d\n", cursor.y);
	refresh();
}

void	ShellRenderer::drawWinner(const int player) const
{
	clear();
	printw("player %d win !\n", player);
	refresh();
}
