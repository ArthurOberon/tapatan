// #include "Game.hpp"
// #include "Game_Graphic.hpp"

// int	main()
// {
// 	char	game_style;


// 	std::cout << "Do you want to play in shell or in a window ? (s/w) " << std::endl;
// 	std::cin >> game_style;

// 	if (game_style == 's')
// 	{
// 		std::cout << "Launch the game in Shell mode\n";

// 		Game game;
// 		initscr();
// 		keypad(stdscr, TRUE);
// 		game.run();
		
// 		endwin();
// 	}
// 	else if (game_style == 'w')
// 	{
// 		std::cout << "Launch the game in Window mode\n";

// 		Game_Graphic game;
// 		game.run();
// 	}
// 	else
// 		std::cout << game_style << " is not a available mode, please use s or w" << std::endl;

// 	return 0;
// }


#include "Game_.hpp"
#include "ShellRenderer.hpp"
#include "ShellInput.hpp"

int	main(void)
{
	int	running = 1;
	int	r = 0;

	s_Action action;

	Game_	game;
	ShellRenderer shellRenderer;
	ShellInput shellInput;

	shellRenderer.draw(game);

	while (game.getGameState() != GameState::Quit)
	{
		action = shellInput.poll();

		r = game.applyAction(action);
		shellRenderer.draw(game);

		if (game.getGameState() == GameState::Playing)
		{
			running = !game.checkWin();
			if (!running)
				game.setGameStateFinish();
			if (r && game.getGameState() == GameState::Playing)
				game.addOneRound();
			
		}


	}

	return 0;
}
