#include "SFMLInput.hpp"

SFMLInput::SFMLInput(/* args */) {}

SFMLInput::~SFMLInput() {}

const s_Action	SFMLInput::poll(sf::RenderWindow & window, const sf::FloatRect hitbox[3][3]) const
{
	sf::Event event;

	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			return (s_Action{ActionType::Quit, Direction::NDF, {-1, -1}});
		}
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
		{
			sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
			for (int i = 0; i < 3; ++i)
			{
				for (int j = 0; j < 3; ++j)
				{
					if (hitbox[i][j].contains(mousePos))
					{
						return (s_Action{ActionType::Enter, Direction::NDF, {j, i}});
					}
				}
			}
			return {ActionType::Enter, Direction::NDF, {-1, -1}};
		}
	}
	return (s_Action{ActionType::NDF, Direction::NDF, {-1, -1}});
}
