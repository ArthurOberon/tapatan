#include "Piece_Mov.hpp"

Piece_Mov::Piece_Mov(/* args */) : c(' '), pos({0, 0})
{
}

Piece_Mov::~Piece_Mov() {}

s_vector2	Piece_Mov::get_pos() const
{
	return this->pos;
}

int	Piece_Mov::is_near_avail_square(const s_vector2 cursor) const
{
	if ((this->pos.y == cursor.y || this->pos.y ==cursor.y - 1 || this->pos.y == cursor.y + 1)
		&& (this->pos.x == cursor.x || this->pos.x ==cursor.x - 1 || this->pos.x == cursor.x + 1))
		return 1;
	return 0;
}

int	Piece_Mov::mov_piece(int turn, s_vector2 cursor, char *cursor_square, char *grid_square)
{
	if (this->c == ' ')
	{
		if ((!turn && *cursor_square == 'X') || (turn && *cursor_square == 'O'))
		{
			this->c = *cursor_square;
			*cursor_square = tolower(*cursor_square);
			this->pos = cursor;
		}
	}
	// if lower == unselect
	else if (cursor.y == this->pos.y && cursor.x == this->pos.x)
	{
		this->c = ' ';
		*cursor_square = toupper(*cursor_square);
	}
	else if (*cursor_square == ' ' && this->is_near_avail_square(cursor))
	{
		*grid_square = ' ';
		*cursor_square = this->c;
		this->c = ' ';
		return 1;
	}
	return 0;
}
