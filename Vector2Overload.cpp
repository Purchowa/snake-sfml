#include "Vector2Overload.h"

std::ostream& operator<<(std::ostream& out, const sf::Vector2f vec)
{
	out << "X: " << vec.x << " Y: " << vec.y;
	return out;
}


sf::Vector2f operator/(const sf::Vector2f& v1, const sf::Vector2f& v2) {
	return { v1.x / v2.x, v1.y / v2.y };
}