#include "Piece_Mov.hpp"

Piece_Mov::Piece_Mov(/* args */) : c(' '), pos({0, 0})
{
}

Piece_Mov::~Piece_Mov() {}

s_vector2	Piece_Mov::get_pos() const
{
	return pos;
}

int	Piece_Mov::is_near_avail_square(const s_vector2 cursor) const
{
	if ((pos.y == cursor.y || pos.y ==cursor.y - 1 || pos.y == cursor.y + 1)
		&& (pos.x == cursor.x || pos.x ==cursor.x - 1 || pos.x == cursor.x + 1))
		return 1;
	return 0;
}

int	Piece_Mov::mov_piece(int turn, s_vector2 cursor, char *cursor_square, char *grid_square)
{
	if (c == ' ')
	{
		if ((!turn && *cursor_square == 'X') || (turn && *cursor_square == 'O'))
		{
			c = *cursor_square;
			*cursor_square = tolower(*cursor_square);
			pos = cursor;
		}
	}
	// if lower == unselect
	else if (cursor.y == pos.y && cursor.x == pos.x)
	{
		c = ' ';
		*cursor_square = toupper(*cursor_square);
	}
	else if (*cursor_square == ' ' && is_near_avail_square(cursor))
	{
		*grid_square = ' ';
		*cursor_square = c;
		c = ' ';
		return 1;
	}
	return 0;
}
