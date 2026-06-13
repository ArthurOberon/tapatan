#include "SFMLRenderer.hpp"


SFMLRenderer::SFMLRenderer(/* args */)
{
	sf::Vector2f init_grid_pos[3][3] = {{{83, 83}, {500, 83}, {916, 83}},
									{{83, 500}, {500, 500}, {916, 500}},
									{{83, 916}, {500, 916}, {916, 916}}};
	
	if (!txtBackground.loadFromFile("ressouces/background.png"))
	{
		std::cerr << "File ./ressouces/background.png not found" << std::endl;
		exit(1);
	}

	if (!txtPieces.loadFromFile("ressouces/pieces.png"))
	{
		std::cerr << "File ./ressouces/piece.png not found" << std::endl;
		exit(1);
	}

	sprtBackground.setTexture(txtBackground);

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			float	x = init_grid_pos[i][j].x - 64;
			float	y = init_grid_pos[i][j].y - 64;

			piecesHitbox[i][j] = sf::FloatRect(x, y, 128, 128);

			sprtPieces[i][j].setPosition(x, y);
			sprtPieces[i][j].setTexture(txtPieces);
			sprtPieces[i][j].setTextureRect(sf::IntRect({0, 0}, {128, 128}));
		}
	}
}

SFMLRenderer::~SFMLRenderer() {}

sf::RenderWindow &	SFMLRenderer::getWindow()
{
	return window;
}

void	SFMLRenderer::openWindow()
{
	if (!window.isOpen())
	{
		window.create(sf::VideoMode(1000, 1000), "Tapatan");
		window.setFramerateLimit(60);
		window.setVerticalSyncEnabled(1);
		window.setPosition(sf::Vector2i(200, 25));
	}
}

void	SFMLRenderer::closeWindow()
{
	window.close();
}

bool	SFMLRenderer::isOpen() const
{
	return window.isOpen();
}

void	SFMLRenderer::draw(const Game &game)
{
	window.clear();

	window.draw(sprtBackground);
	drawPieces(game);

	// if (game.getGameState() == GameState::Winner)
		// drawWinner();

	window.display();
}

void	SFMLRenderer::drawPieces(const Game &game)
{
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			char c = game.getGridCell({j, i});
			int	frame = 0;

			if (c == 'X' || c == 'x')
				frame = 1;
			else if (c == 'O' || c == 'o')
				frame = 2;
			else
				frame = 0;

			sprtPieces[j][i].setTextureRect(sf::IntRect({frame * 128, 0}, {128, 128}));

			if (c == 'x' || c == 'o')
				sprtPieces[j][i].setColor(sf::Color(255, 255, 255, 128)); // 50% transparent
			else
				sprtPieces[j][i].setColor(sf::Color(255, 255, 255, 255)); // 0% transparent

			this->window.draw(sprtPieces[j][i]);
		}
	}
}

const sf::FloatRect (& SFMLRenderer::getPiecesHitbox() const)[3][3]
{
	return piecesHitbox;
}
