#include "Display.hpp"

Display::Display(/* args */)
{
	sf::Vector2f init_grid_pos[3][3] = {{{83, 83}, {500, 83}, {916, 83}},
									{{83, 500}, {500, 500}, {916, 500}},
									{{83, 916}, {500, 916}, {916, 916}}};
	
	if (!this->txt_background.loadFromFile("Ressouces/background.png"))
	{
		std::cerr << "File ./Ressouces/background.png not found" << std::endl;
		exit(1);
	}

	if (!this->txt_piece.loadFromFile("Ressouces/pieces.png"))
	{
		std::cerr << "File ./Ressouces/piece.png not found" << std::endl;
		exit(1);
	}

	this->sprt_background.setTexture(this->txt_background);

	this->sprt_p_offset = SPRITE_P_SIZE / 2;

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			this->sprts_pieces[i][j].sprite.setPosition(init_grid_pos[i][j].x - this->sprt_p_offset,
														init_grid_pos[i][j].y - this->sprt_p_offset);
			this->sprts_pieces[i][j].color = 0;
			this->sprts_pieces[i][j].sprite.setTexture(this->txt_piece);
			this->sprts_pieces[i][j].sprite.setTextureRect(sf::IntRect({0, 0}, {128, 128}));
		}
	}
}

Display::~Display() {}

void	Display::display_game(char grid[3][3])
{
	// while (this->window.isOpen())
	// {
	// 	sf::Event event;
	// 	while (this->window.pollEvent(event))
	// 	{
	// 		if (event.type == sf::Event::Closed)
	// 			this->window.close();
	// 		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	// 		{
	// 			sf::Vector2f mousePos = this->window.mapPixelToCoords(sf::Mouse::getPosition(this->window));
	// 			for (int i = 0; i < 3; ++i)
	// 			{
	// 				for (int j = 0; j < 3; ++j)
	// 				{
	// 					sf::Sprite s = this->sprts_pieces[i][j].sprite;

	// 					if (s.getGlobalBounds().contains(mousePos)) // --> sprite click on by mouse ?
	// 					{
	// 						game.set_cursor((s_vector2){mousePos.x, mousePos.y});
	// 						game.key_enter_handle();
	// 					}
	// 				}
	// 			}
	// 		}
	// 	}
	this->window.clear();
	this->window.draw(sprt_background);

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			s_sprite s = this->sprts_pieces[i][j];

			if (grid[j][i] == 'X' || grid[j][i] == 'x')
				s.color = 1;
			else if (grid[j][i] == 'O' || grid[j][i] == 'o')
				s.color = 2;
			else
				s.color = 0;
			if (grid[j][i] == 'x' || grid[j][i] == 'o')
			{
				this->sprts_pieces[i][j].sprite.setColor(sf::Color(255, 255, 255, 128)); // 50% transparent
			}
			else
				this->sprts_pieces[i][j].sprite.setColor(sf::Color(255, 255, 255, 255)); // 0% transparent
			s.sprite.setTextureRect(sf::IntRect({s.color * 128, 0}, {128, 128}));

			this->window.draw(s.sprite);
		}
	}
	this->window.display();
}
