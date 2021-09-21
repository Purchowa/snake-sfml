#pragma once

#include "SFML/Graphics.hpp"
#include <iostream>

class Map: public sf::Drawable
{
public:
	Map(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Vector2f& snake_head_size);
private:
	virtual void draw(sf::RenderTarget& AppWindow, sf::RenderStates states) const;
	const sf::Vector2f& snake_head_size;
	bool grid;
	const sf::Vector2i grid_count;

	sf::Vector2<sf::VertexArray> grid_line;

	sf::RectangleShape map_box;
	sf::Vector2f grid_startPos;
	sf::Vector2f grid_endPos;

};
