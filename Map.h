#pragma once

#include "SFML/Graphics.hpp"
#include <iostream>

class Map: public sf::Drawable
{
public:
	Map(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Vector2f& HEAD_SIZE);

private:
	bool grid;
	sf::Vector2<sf::VertexArray> grid_line;
	sf::RectangleShape map_box;

	void initLines();
	virtual void draw(sf::RenderTarget& AppWindow, sf::RenderStates states) const;
};
