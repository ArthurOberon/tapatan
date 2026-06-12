#include "Game.hpp"
#include "Game_Graphic.hpp"

int	main()
{
	char	game_style;


	std::cout << "Do you want to play in shell or in a window ? (s/w) " << std::endl;
	std::cin >> game_style;

	if (game_style == 's')
	{
		std::cout << "Launch the game in Shell mode\n";

		Game game;
		initscr();
		keypad(stdscr, TRUE);
		game.run();
		
		endwin();
	}
	else if (game_style == 'w')
	{
		std::cout << "Launch the game in Window mode\n";

		Game_Graphic game;
		game.run();
	}
	else
		std::cout << game_style << " is not a available mode, please use s or w" << std::endl;

	return 0;
}
