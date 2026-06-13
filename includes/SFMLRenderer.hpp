#pragma once

#include <SFML/Graphics.hpp>
#include "Game.hpp"

class SFMLRenderer
{
private:
    sf::RenderWindow window;

    sf::Texture txtBackground;
    sf::Texture txtPieces;

    sf::Sprite sprtBackground;
    sf::Sprite sprtPieces[3][3];
	sf::FloatRect piecesHitbox[3][3];



public:
	SFMLRenderer(/* args */);
	~SFMLRenderer();

	sf::RenderWindow &	getWindow();
	void	openWindow();
	void	closeWindow();
	bool	isOpen() const;

	void	draw(const Game &game);
	void	drawBoard(const Game &game);
	void	drawPieces(const Game &game);

	const sf::FloatRect (& getPiecesHitbox() const)[3][3];
};
