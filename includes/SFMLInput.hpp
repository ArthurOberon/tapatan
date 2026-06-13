#pragma once

#include "SFMLRenderer.hpp"

class SFMLInput
{
private:
	/* data */
public:
	SFMLInput(/* args */);
	~SFMLInput();

	const s_Action	poll(sf::RenderWindow & window, const sf::FloatRect hitbox[3][3]) const;
};
