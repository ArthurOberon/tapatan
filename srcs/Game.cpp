#include "Game.hpp"

Game::Game(/* args */) : round(0), cursor({0, 0})
{
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			this->grid[i][j] = ' ';
		}
	}
}

Game::~Game() {}

void	Game::draw_result() const
{
	clear();
	printw("player %d win !\n", this->round % 2 + 1);
	refresh();
}

void	Game::draw_game()
{
	clear();
	for (int y = 0; y < 3; ++y)
	{
		for (int x = 0; x < 3; ++x)
		{
			if (x == this->cursor.x && y == this->cursor.y)
				attron(A_REVERSE);

			printw("[%c] ", this->grid[y][x]);

			if (x == this->cursor.x && y == this->cursor.y)
				attroff(A_REVERSE);
		}
		printw("\n");
	}
	printw("turn : player %d\n", this->round % 2 + 1);
	// printw("x : %d\n", this->cursor.x);
	// printw("y : %d\n", this->cursor.y);
	refresh();
}

void	Game::key_arrow_handle(const int key)
{
	switch (key)
	{
		case KEY_UP:
			if (this->cursor.y > 0)
				--this->cursor.y;
			break;

		case KEY_DOWN:
			if (this->cursor.y < 2)
				++this->cursor.y;
			break;

		case KEY_LEFT:
			if (this->cursor.x > 0)
				--this->cursor.x;
			break;

		case KEY_RIGHT:
			if (this->cursor.x < 2)
				++this->cursor.x;
			break;

		default:
			break;
	}
}

int	Game::key_enter_handle(const int key)
{
	int	r = 0;
	int	turn = this->round % 2;
	char	*cursor_square;
	s_vector2 mov_p_pos;

	if (key == '\n' || key == ' ')
	{
		cursor_square = &(this->grid[this->cursor.y][this->cursor.x]);
		if (this->round < 6)
		{
			if (*cursor_square == ' ')
			{
				if (turn == 0)
					*cursor_square = 'X';
				else
					*cursor_square = 'O';
				r = 1;
			}
		}
		else
		{
			mov_p_pos = this->piece_mov.get_pos();
			r = this->piece_mov.mov_piece(turn, this->cursor, cursor_square, &(grid[mov_p_pos.y][mov_p_pos.x]));
		}
	}

	return r;
}

int	Game::check_win() const
{
	char	c;
	int	count = 0;

	if (round % 2 == 0)
		c = 'X';
	else
		c = 'O';

	// check vert
	for (int x = 0; x < 3; ++x)
	{
		count = 0;
		for (int y = 0; y < 3; ++y)
		{
			if (grid[y][x] == c)
			{
				++count;
				if (count == 3)
					return 1;
			}
		}
	}
	// check horiz
	for (int y = 0; y < 3; ++y)
	{
		count = 0;
		for (int x = 0; x < 3; ++x)
		{
			if (grid[y][x] == c)
			{
				++count;
				if (count == 3)
					return 1;
			}
		}
	}
	// check diag
	if ((grid[0][0] == c && grid[1][1] == c && grid[2][2] == c)
		|| (grid[0][2] == c && grid[1][1] == c && grid[2][0] == c))
	{
		return 1;
	}

	return 0;
}

void	Game::run()
{
	int running = 1;
	int r = 0;
	int	key;

	while (running)
	{
		this->draw_game();
		key = getch();
		this->key_arrow_handle(key);
		r = this->key_enter_handle(key);
		running = !this->check_win();
		this->round += r;
	}

	while (1)
	{
		this->draw_game();
		key = getch();
		this->key_arrow_handle(key);
		if (key == '\n' || key == ' ')
			break;
	}

	while (1)
	{
		this->draw_result();
		key = getch();
		if (key == '\n' || key == ' ')
			break;
	}
}
