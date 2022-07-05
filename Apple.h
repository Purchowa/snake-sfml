#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include "Snake.h"

// NOTE: Mo�na da� niewidzialn� lini�, kt�ra b�dzie m�wi� czy nast�pi�a kolizja

class Apple : public sf::Drawable
{
public:
	Apple(const Snake& snakeHead);
	bool appleCollision();
	void updatePosition();
private:
	const Snake& snakeObj;
	sf::RectangleShape apple;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

