#include "Apple.h"

Apple::Apple(const Snake& snakeObj) : snakeObj(snakeObj)
{
	apple.setOrigin(snakeObj.snake_head.getOrigin());

	this->updatePosition();

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
	sf::Vector2f zeroPosition;
	int n = 0;
	do
	{
		sf::Vector2i randApple{
		rand() % static_cast<int>(snakeObj.MAP_SIZE.x / snakeObj.HEAD_SIZE.x),
		rand() % static_cast<int>(snakeObj.MAP_SIZE.y / snakeObj.HEAD_SIZE.y)
		};

		zeroPosition = {
			randApple.x * snakeObj.HEAD_SIZE.x + snakeObj.MAP_POS.x + snakeObj.snake_head.getOrigin().x,
		   randApple.y * snakeObj.HEAD_SIZE.y + snakeObj.MAP_POS.y + snakeObj.snake_head.getOrigin().y
		};

		std::cout << (n++ > 1 ? n : 0) << '\n';
		
	}while (bodyContainsApple(zeroPosition));


	apple.setPosition(zeroPosition);
}

bool Apple::bodyContainsApple(const sf::Vector2f applePos)
{
	if (snakeObj.snake_head.getPosition() == applePos) {
		return true;
	}

	for (unsigned i = 0; i < snakeObj.part_vertices.size(); i += snakeObj.VERTICES_NUMBER)
	{
		if (snakeObj.shapeContaintsPoint(&snakeObj.part_vertices[i], applePos))
		{
			return true;
		}
	}

	return false;
}

void Apple::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(apple);
}
