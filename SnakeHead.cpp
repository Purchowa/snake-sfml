#include "SnakeHead.h"

SnakeHead::SnakeHead(const sf::Vector2f& h_size, const sf::Vector2f& t_size)
	: head(h_size), tongue(t_size), // setting SIZE with constructor.
	Rays(sf::Lines, VERTEX_SIZ), rayOrigin{h_size / 2.f}
{
	// tongue.setOrigin(h_size / 2.f);
	// tongue.setPosition({ head.getSize().x / 2.f,  head.getSize().y / 4.f });
	// tongue.setPosition({h_size.x / 2.f - t_size.x / 2.f,  h_size.y / 2.f  - t_size.y });

	Rays[0].position = { 0, -h_size.y };
	Rays[1].position = { 0, 0 };

	for (int i = 0; i < VERTEX_SIZ; i++) {
		Rays[i].position += rayOrigin;
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
	// std::cout << this->getPosition() + Rays[0].position - rayOrigin << '\n';
	target.draw(head, states);
	//target.draw(Rays, states);
}

