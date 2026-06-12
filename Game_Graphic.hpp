#pragma once

#include <iostream>
#include "Piece_Mov.hpp"
#include "vector2.hpp"
#include "Display.hpp"

using namespace std;

class Game_Graphic
{
private:
	char	grid[3][3];
	int	round;
	s_vector2	cursor;
	Piece_Mov	piece_mov;
	Display	game_display;

	// void	draw_game();
	// void	key_arrow_handle(const int key);
	int	check_win() const;
	// void	draw_result() const;
	
	public:
	Game_Graphic(/* args */);
	~Game_Graphic();
	void	run();
	int	key_enter_handle();
	void	set_cursor(s_vector2 mouse);
	

};
