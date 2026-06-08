#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

int TILD_SIZE_X = 490;
int TILD_SIZE_Y = 455;

struct s_piece
{
	int x, y;
	int col, row;
	int kind; //0 = none, 1 = player_1, 2 = player_2
};


int main()
{
	sf::RenderWindow	window(sf::VideoMode(1080, 1000), "Tapatan");
	window.setFramerateLimit(60);

	// sf::CircleShape	shape(20);

	sf::Texture txt_background, txt_piece;
	if (!txt_background.loadFromFile("background.png"))
	{
		std::cerr << "File ./background.png not found" << std::endl;
		return (1);
	}

	if (!txt_piece.loadFromFile("piece.png"))
	{
		std::cerr << "File ./piece.png not found" << std::endl;
		return (1);
	}

	sf::Sprite sprt_background(txt_background), sprt_piece(txt_piece);

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

	int click = 0;
	sf::Vector2i pos_click;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				++click;
				pos_click = sf::Mouse::getPosition(window);
				cout << "pos_click : " << pos_click.x << " " << pos_click.y << endl;
				pos_click.x = pos_click.x / TILD_SIZE_X;
				pos_click.y = pos_click.y / TILD_SIZE_Y;
				cout << "pos_click : " << pos_click.x << " " << pos_click.y << endl;
				cout << "pos wanted : " << grid[0][1].col << " " << grid[0][1].row << endl;
				for (int i = 0; i < 3; ++i)
				{
					for (int j = 0; j < 3; ++j)
					{
						if (pos_click == sf::Vector2i(grid[i][j].col, grid[i][j].row))
						{
							grid[i][j].kind = (click % 2) + 1;
							std::cout << "Piece drop !" << std::endl;
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
					if (p.kind != 0)
					{
						sf::Vector2f pos_piece(p.x, p.y);
						sprt_piece.setPosition(pos_piece);
						window.draw(sprt_piece);
					}
				}
			}
			window.display();
		}
	}

    return 0;
}
