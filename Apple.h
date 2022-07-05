#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include "Snake.h"
#include "Vector2Overload.h"

// NOTE: Mo¿na daæ niewidzialn¹ liniê, która bêdzie mówiæ czy nast¹pi³a kolizja

class Apple : public sf::Drawable
{
public:
	Apple(const Snake& snakeHead);
	bool appleCollision();
	void updatePosition();
private:
	const Snake& snakeObj;
	sf::RectangleShape apple;

	bool bodyContainsApple(const sf::Vector2f applePos);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

