#include "Ray.h"

Ray::Ray(const int rayCount, const float length, const sf::Vector2f origin)
	: Rays(2ULL * rayCount)
{
	const double PI = atan(1)*4;

	for (int i = 0; i < 2 * rayCount; i += 2) {
		Rays[i].position = origin;
		Rays[i].color = sf::Color::Cyan;
	}
	for (int i = 1, j = 0; i < 2 * rayCount; i += 2, j++) {
		Rays[i].position = {origin.x + static_cast<float>(cos(-PI * j / (rayCount-1LL))) * length, origin.y + static_cast<float>(sin(-PI * j / (rayCount-1LL))) * length };
		Rays[i].color = sf::Color::Cyan;
	}
	return;
}

sf::Vertex& Ray::operator[](const int index)
{
	return Rays[index];
}

void Ray::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(&Rays[0], Rays.size(), sf::Lines, states);
}
