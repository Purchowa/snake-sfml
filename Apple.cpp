#include "Apple.h"

Apple::Apple(const Snake& snakeObj) : snakeObj(snakeObj)
{
	sf::Vector2i randApple{
	rand() % static_cast<int>(snakeObj.MAP_SIZE.x / snakeObj.HEAD_SIZE.x),
	rand() % static_cast<int>(snakeObj.MAP_SIZE.y / snakeObj.HEAD_SIZE.y)
	};
	apple.setOrigin(snakeObj.snake_head.getOrigin());
	apple.setPosition(
		{ randApple.x * snakeObj.HEAD_SIZE.x + snakeObj.MAP_POS.x + snakeObj.snake_head.getOrigin().x },
		{ randApple.y * snakeObj.HEAD_SIZE.y + snakeObj.MAP_POS.y + snakeObj.snake_head.getOrigin().y }
	);
	apple.setFillColor(sf::Color::Green);
	apple.setSize(snakeObj.HEAD_SIZE);
}

bool Apple::appleCollision()
{
	if (snakeObj.snake_head.getPosition() == apple.getPosition())
		return true;

	return false;
}

void Apple::updatePosition()
{
	sf::Vector2i randApple{
	rand() % static_cast<int>(snakeObj.MAP_SIZE.x / snakeObj.HEAD_SIZE.x),
	rand() % static_cast<int>(snakeObj.MAP_SIZE.y / snakeObj.HEAD_SIZE.y)
	};

	apple.setPosition(
		{ randApple.x * snakeObj.HEAD_SIZE.x + snakeObj.MAP_POS.x + snakeObj.snake_head.getOrigin().x },
		{ randApple.y * snakeObj.HEAD_SIZE.y + snakeObj.MAP_POS.y + snakeObj.snake_head.getOrigin().y }
	);
}

void Apple::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(apple);
}
