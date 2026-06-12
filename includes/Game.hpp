#pragma once

#include <iostream>
#include <ncurses.h>
#include "Piece_Mov.hpp"
#include "vector2.hpp"

using namespace std;

class Game
{
private:
	char	grid[3][3];
	int	round;
	s_vector2	cursor;
	Piece_Mov	piece_mov;

	void	draw_game();
	void	key_arrow_handle(const int key);
	void	draw_result() const;
	int	key_enter_handle(const int key);
	int	check_win() const;
	
	public:
	Game(/* args */);
	~Game();
	void	run();
	

};
