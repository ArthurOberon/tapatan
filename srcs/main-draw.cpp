#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

int TILD_SIZE_X = 128;
int TILD_SIZE_Y = 128;
int	SPRITE_SIZE = 128;

struct s_vector2
{
	int	x;
	int	y;
};

s_vector2 grid_pos[3][3] = {{{83, 83}, {500, 83}, {916, 83}},
							{{83, 500}, {500, 500}, {916, 500}},
							{{83, 916}, {500, 916}, {916, 916}}};

struct s_piece
{
	int x, y;
	int col, row;
	int kind; //0 = none, 1 = player_1, 2 = player_2
};


int main()
{
	sf::RenderWindow	window(sf::VideoMode(1000, 1000), "Tapatan");
	window.setFramerateLimit(60);

	// sf::CircleShape	shape(20);

	sf::Texture txt_background, txt_piece;
	if (!txt_background.loadFromFile("Ressouces/asprite-background.png"))
	{
		std::cerr << "File ./background.png not found" << std::endl;
		return (1);
	}

	if (!txt_piece.loadFromFile("Ressouces/pieces.png"))
	{
		std::cerr << "File ./piece.png not found" << std::endl;
		return (1);
	}

	sf::Sprite sprt_background(txt_background);

	sf::Sprite  sprt_piece[3][3];


	s_piece grid[3][3];

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			grid[i][j].x = j * TILD_SIZE_X;
			grid[i][j].y = i * TILD_SIZE_Y;
			grid[i][j].col = j;
			grid[i][j].row = i;
			grid[i][j].kind = 0;
		}
	}

	int offset = SPRITE_SIZE / 2;
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			sf::Sprite &s = sprt_piece[i][j];

			s.setTexture(txt_piece);

			sf::Vector2f pos_piece(grid_pos[i][j].x - offset, grid_pos[i][j].y - offset);
			s.setPosition(pos_piece);
			s.setTextureRect(sf::IntRect({0, 0}, {128, 128}));
		}
	}

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
				for (int i = 0; i < 3; ++i)
				{
					for (int j = 0; j < 3; ++j)
					{
						s_piece &p = grid[i][j];
						sf::Sprite s = sprt_piece[i][j];

						if (s.getGlobalBounds().contains(mousePos)) // --> sprite click on by mouse ?
						{
							// s.setTextureRect(sf::IntRect({p.kind * 128, 0}, {128, 128}));
							// p.kind = 2;
						}
					}
				}
			}
		}
		window.clear();
		window.draw(sprt_background);

		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				s_piece p = grid[i][j];
				sf::Sprite s = sprt_piece[i][j];
				s.setTextureRect(sf::IntRect({p.kind * 128, 0}, {128, 128}));


				window.draw(s);
			}
		}
		window.display();
	}

    return 0;
}



// sprite.setColor(sf::Color(255, 255, 255, 128)); // 50% transparent
// sprite.getGlobalBounds().contains(mousePos) --> sprite click on by mouse ?
