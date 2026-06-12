#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#define SPRITE_P_SIZE 128

struct s_sprite
{
	// s_vector2	pos_grid;
	// sf::Vector2f	pos_window;
	sf::Sprite		sprite;
	int	color;
};

class Display
{
private:
	sf::Texture	txt_background;
	sf::Texture	txt_piece;

	sf::Sprite sprt_background;
	
	int	sprt_p_offset;
	
public:
	sf::RenderWindow	window;
	s_sprite sprts_pieces[3][3];

	Display(/* args */);
	~Display();

	void	display_game(char grid[3][3]);
};
