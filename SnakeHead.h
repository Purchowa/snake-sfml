#pragma once
#include "SFML/Graphics.hpp"

class SnakeHead : public sf::Drawable, public sf::Transformable
{
public:
	SnakeHead(const sf::Vector2f& h_size, const sf::Vector2f& t_size);
	void updateFillColorHead(const sf::Color& h_color);
	void updateFillColorTongue(const sf::Color& t_color);

private:
	const static int VERTEX_SIZ = 2;
	sf::RectangleShape head;
	sf::RectangleShape tongue;
	sf::VertexArray Rays;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};