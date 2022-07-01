#include "Apple.h"

Apple::Apple(const sf::Color& color) 
{
	sf::Vector2i randApple{
	rand() % static_cast<int>(MAP_SIZE.x / HEAD_SIZE.x),
	rand() % static_cast<int>(MAP_SIZE.y / HEAD_SIZE.y)
	};
	apple.setOrigin(snake_head.getOrigin());
	apple.setPosition(
		{ randApple.x * HEAD_SIZE.x + map_pos.x + snake_head.getOrigin().x },
		{ randApple.y * HEAD_SIZE.y + map_pos.y + snake_head.getOrigin().y }
	);
	apple.setFillColor(color);
	apple.setSize(HEAD_SIZE);
}

void Apple::appleCollision()
{
	if (snake_head.getPosition() == apple.getPosition())
	{
		std::cout << apple.getPosition().x << "\n";
	}
	return;
}

void Apple::updatePositionApple()
{
	return;
}

void Apple::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(apple);
}
