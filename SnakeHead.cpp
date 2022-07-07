#include "SnakeHead.h"

SnakeHead::SnakeHead(const sf::Vector2f& h_size, const sf::Vector2f& t_size)
	: head(h_size), tongue(t_size), // setting SIZE with constructor.
	Rays(sf::Lines, VERTEX_SIZ)
{
	tongue.setOrigin(tongue.getSize() / 2.f);
	tongue.setPosition({ head.getSize().x / 2.f,  head.getSize().y / 4.f });
	// tongue.setPosition({h_size.x / 2.f - t_size.x / 2.f,  h_size.y / 2.f  - t_size.y });

	Rays[0].position = { h_size.x / 2.f, h_size.y / 2.f - h_size.y };
	Rays[1].position = { h_size.x / 2.f, h_size.y / 2.f };

	for (int i = 0; i < VERTEX_SIZ; i++) {
		Rays[i].color = sf::Color::Blue;
	}
}

void SnakeHead::updateFillColorHead(const sf::Color& h_color)
{
	head.setFillColor(h_color);
}

void SnakeHead::updateFillColorTongue(const sf::Color& t_color)
{
	tongue.setFillColor(t_color);
}

void SnakeHead::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform.combine(getTransform());
	// It combines earlier states of transformation with current ones.
	// states.transform *= getTransform(); // Operator '*=' was overloaded
	target.draw(head, states);
	// target.draw(tongue, states);
	target.draw(Rays, states);
}

