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

void	ShellRenderer::draw(const Game & game)
{
	clear();

	if (game.getGameState() == GameState::Finished)
		drawWinner(game);
	else
		drawPieces(game);
	refresh();
}

void	ShellRenderer::drawPieces(const Game & game)
{
	s_vector2	cursor(game.getCursor());

	for (int y = 0; y < 3; ++y)
	{
		for (int x = 0; x < 3; ++x)
		{
			if (x == cursor.x && y == cursor.y)
				attron(A_REVERSE);

			printw("[%c] ", game.cell({x, y}));

			if (x == cursor.x && y == cursor.y)
				attroff(A_REVERSE);
		}
		printw("\n");
	}
	printw("turn : player %d\n", game.getPlayerTurn());
	// printw("x : %d\n", cursor.x);
	// printw("y : %d\n", cursor.y);
}

void	ShellRenderer::drawWinner(const Game & game) const
{
	int	w = game.getPlayerTurn() == 1 ? 'X' : 'O';

	for (int y = 0; y < 3; ++y)
	{
		for (int x = 0; x < 3; ++x)
		{
			if (game.cell(x, y) == w)
			{
				attron(A_REVERSE);
				printw("[%c] ", game.cell({x, y}));
				attroff(A_REVERSE);
			}
			else
				printw("[%c] ", game.cell({x, y}));
		}
		printw("\n");
	}
	printw("player %d win !\n", game.getPlayerTurn());
}
