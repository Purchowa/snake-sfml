#include "Vector2Overload.h"

std::ostream& operator<<(std::ostream& out, const sf::Vector2f vec)
{
	out << "X: " << vec.x << " Y: " << vec.y;
	return out;
}
