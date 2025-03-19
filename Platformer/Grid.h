#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Gravity.h"


class Grid
{
private:

	int spacing;
	sf::Color baseColor;


public:

	Grid(int spacing = 50);

	void render(sf::RenderWindow& window, std::vector<Gravity>& gravities);

};

