#include "Game.hpp"
#include "ShellRenderer.hpp"
#include "ShellInput.hpp"
#include "SFMLRenderer.hpp"
#include "SFMLInput.hpp"

void	playShell(Game & game)
{
	int	running = 1;
	int	r = 0;

	s_Action action;

	ShellRenderer renderer;
	ShellInput input;

	renderer.draw(game);

	while (game.getGameState() != GameState::Quit)
	{
		r = 0;
		action = input.poll();

		r = game.applyAction(action);
		if (r == -1)
			break ;
		renderer.draw(game);

		if (game.getGameState() == GameState::Playing)
		{
			running = !game.checkWin();
			if (!running)
				game.setGameStateFinish();
			if (r && game.getGameState() == GameState::Playing)
				game.addOneRound();
		}
	}
}

void	playSFML(Game & game)
{
	int	running = 1;
	int	r = 0;

	s_Action action;

	SFMLRenderer	renderer;
	SFMLInput	input;

	renderer.openWindow();

	renderer.draw(game);

	while (renderer.isOpen())
	{
		r = 0;
		action = input.poll(renderer.getWindow(), renderer.getPiecesHitbox());
		if (action.type != ActionType::NDF)
			r = game.applyAction(action);

		if (r == -1 || game.getGameState() == GameState::Quit)
		{
			renderer.closeWindow();
			break ;
		}
		renderer.draw(game);

		if (game.getGameState() == GameState::Playing)
		{
			running = !game.checkWin();
			if (!running)
				game.setGameStateFinish();
			if (r && game.getGameState() == GameState::Playing)
				game.addOneRound();
		}
	}
}

int	main(void)
{
	Game	game;
	char	gameStyle;

	std::cout << "Do you want to play in shell or in a window ? (s/w) " << std::endl;
	std::cin >> gameStyle;

	if (gameStyle == 's')
		playShell(game);
	else if (gameStyle == 'w')
		playSFML(game);
	else
	std::cout << gameStyle << " is not a available mode, please use s or w" << std::endl;
	return 0;
}
