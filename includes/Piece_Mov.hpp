#pragma once

#include <iostream>
#include "vector2.hpp"

class Piece_Mov
{
private:
	char c;
	s_vector2	pos;

public:
	Piece_Mov(/* args */);
	~Piece_Mov();

	int	mov_piece(int turn, s_vector2 cursor, char *cursor_square, char *grid_square);

	s_vector2 get_pos() const;

	int is_near_avail_square(const s_vector2 cursor) const;
};
