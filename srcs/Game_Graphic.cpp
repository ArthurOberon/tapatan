#include "Game_Graphic.hpp"

Game_Graphic::Game_Graphic(/* args */) : round(0), cursor({0, 0})
{
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			this->grid[i][j] = ' ';
		}
	}
}

Game_Graphic::~Game_Graphic() {}

int	Game_Graphic::key_enter_handle()
{
	int	r = 0;
	int	turn = this->round % 2;
	char	*cursor_square;
	s_vector2 mov_p_pos;

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

	return r;
}

int	Game_Graphic::check_win() const
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

void	Game_Graphic::run()
{
	int	r = 0;
	
	this->game_display.window.create(sf::VideoMode(1000, 1000), "Tapatan");
	this->game_display.window.setFramerateLimit(60);
	

	while (this->game_display.window.isOpen())
	{
		r = 0;
		this->game_display.display_game(this->grid);

		sf::Event event;
		while (this->game_display.window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				this->game_display.window.close();
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				sf::Vector2f mousePos = this->game_display.window.mapPixelToCoords(sf::Mouse::getPosition(this->game_display.window));
				for (int i = 0; i < 3; ++i)
				{
					for (int j = 0; j < 3; ++j)
					{
						sf::Sprite s = this->game_display.sprts_pieces[i][j].sprite;

						if (s.getGlobalBounds().contains(mousePos))
						{
							this->set_cursor((s_vector2){i, j});
							r = this->key_enter_handle();
						}
					}
				}
			}
			if (this->check_win())
			{
				this->game_display.display_game(this->grid);
				std::cout << "player " << this->round % 2 + 1 << " win !" << std::endl;
				int	click = 0;
				while (1)
				{
					if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
					{
						while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {}
						++click;
					}
					if (click == 2)
						break;
				}
				this->game_display.window.close();
			}
			this->round += r;
		}
	}
}

void		Game_Graphic::set_cursor(s_vector2 mouse)
{
	this->cursor = mouse;
}
