#include <iostream>
#include <ncurses.h>

using namespace std;

struct s_vector2
{
	int	x;
	int	y;
};


void	draw_end(int turn)
{
	clear();
	printw("player %d win !\n", turn);
	refresh();
}

void	draw_game(int turn, s_vector2 cursor, char grid[3][3])
{
	clear();
	for (int y = 0; y < 3; ++y)
	{
		for (int x = 0; x < 3; ++x)
		{
			if (x == cursor.x && y == cursor.y)
				attron(A_REVERSE);

			printw("[%c] ", grid[y][x]);

			if (x == cursor.x && y == cursor.y)
				attroff(A_REVERSE);
		}
		printw("\n");
	}
	printw("turn : player %d\n", turn);
	printw("x : %d\n", cursor.x);
	printw("y : %d\n", cursor.y);
	refresh();
}

void	key_arrow_handle(int key, s_vector2 *cursor)
{
	switch (key)
	{
		case KEY_UP:
			if (cursor->y > 0)
				--cursor->y;
			break;

		case KEY_DOWN:
			if (cursor->y < 2)
				++cursor->y;
			break;

		case KEY_LEFT:
			if (cursor->x > 0)
				--cursor->x;
			break;

		case KEY_RIGHT:
			if (cursor->x < 2)
				++cursor->x;
			break;

		default:
			break;
	}
}

int	key_enter_handle(int key, int round, s_vector2 cursor, char grid[3][3], char *move_piece, s_vector2 *mov_p_vec)
{
	int	r = 0;
	if (key == KEY_ENTER || key == ' ')
	{
		if (round < 6)
		{
			if (grid[cursor.y][cursor.x] == ' ')
			{
				if (round % 2 == 0)
					grid[cursor.y][cursor.x] = 'X';
				else
					grid[cursor.y][cursor.x] = 'O';
				r = 1;
			}
		}
		else if (*move_piece == ' ')
		{
			if (round % 2 == 0 && grid[cursor.y][cursor.x] == 'X')
			{
				*move_piece = 'X';
				grid[cursor.y][cursor.x] = 'x';
				*mov_p_vec = cursor;
			}
			else if (round % 2 != 0 && grid[cursor.y][cursor.x] == 'O')
			{
				*move_piece = 'O';
				grid[cursor.y][cursor.x] = 'o';
				*mov_p_vec = cursor;
			}
		}
		else
		{
			if (grid[cursor.y][cursor.x] == ' ')
			{
				if ((mov_p_vec->y == cursor.y || mov_p_vec->y == cursor.y - 1 || mov_p_vec->y == cursor.y + 1)
					&& (mov_p_vec->x == cursor.x || mov_p_vec->x == cursor.x - 1 || mov_p_vec->x == cursor.x + 1))
				{
					grid[mov_p_vec->y][mov_p_vec->x] = ' ';
					grid[cursor.y][cursor.x] = *move_piece;
					*move_piece = ' ';
					r = 1;
				}
			}
		}
	}

	return r;
}

int	check_win(char grid[3][3], int round)
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

int main()
{
	char grid[3][3];

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			grid[i][j] = ' ';
		}
	}

	int	round = 0;
	int r = 0;

	s_vector2	cursor = {0, 0};

	int	key;
	
	char	move_piece = ' ';
	s_vector2	mov_p_vec;

	int running = 1;

	initscr();
	keypad(stdscr, TRUE);

	while (running)
	{
		draw_game(round % 2 + 1, cursor, grid);
		key = getch();
		key_arrow_handle(key, &cursor);
		r = key_enter_handle(key, round, cursor, grid, &move_piece, &mov_p_vec);
		running = !check_win(grid, round);
		round += r;
	}
	draw_game(round % 2 + 1, cursor, grid);
	getch();
	draw_end(round % 2 + 1);
	getch();

	endwin();
	return 0;
}
