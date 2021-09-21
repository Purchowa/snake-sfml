#include "Map.h"

/*
Calling multiple times draw function (like 200 times)
grid(true) == 2500 fps --- big fps drops
grid(false) == 3800fps

Calling two times draw function for whole grid - using sf::VertexArray
grid(true) == 3800fps --- almost zero fps drops
grid(false) == 3800fps
*/

Map::Map(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Vector2f& head_size)
	: snake_head_size(head_size), grid(true), grid_count((size.y / head_size.y) * 2, (size.x / head_size.x) * 2),
	grid_line( sf::VertexArray(sf::Lines, grid_count.x), sf::VertexArray(sf::Lines, grid_count.y) )
{
	this->map_box.setSize(size);
	this->map_box.setPosition(position); // left top corner

	this->map_box.setFillColor(sf::Color::Black);
	this->map_box.setOutlineThickness(1.f);

	grid_startPos.x = position.x;
	grid_startPos.y = position.y;

	grid_endPos.x = position.x + size.x;
	grid_endPos.y = position.y + size.y;
	
	sf::Color grid_color{ 192, 192, 192, 64 };
	unsigned int i = 0;
	for (float x = grid_startPos.x; x < grid_endPos.x; x += snake_head_size.x)
	{
		grid_line.x[i].position = sf::Vector2f(x, grid_startPos.y);
		grid_line.x[i].color = grid_color;
		i++;
		grid_line.x[i].position = sf::Vector2f(x, grid_endPos.y);
		grid_line.x[i].color = grid_color;
		i++;
	}
	i = 0;
	for (float y = grid_startPos.y; y < grid_endPos.y; y += snake_head_size.y)
	{
		grid_line.y[i].position = sf::Vector2f(grid_startPos.x, y);
		grid_line.y[i].color = grid_color;
		i++;
		grid_line.y[i].position = sf::Vector2f(grid_endPos.x, y);
		grid_line.y[i].color = grid_color;
		i++;
	}
	
	return;
}

void Map::draw(sf::RenderTarget& AppWindow, sf::RenderStates states) const
{
	AppWindow.draw(map_box);
	if (grid)
	{
		AppWindow.draw(grid_line.x);
		AppWindow.draw(grid_line.y);
	}	
}

