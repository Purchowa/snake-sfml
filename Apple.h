#pragma once
#include "Snake.h"
#include "SFML/Graphics.hpp"
#include <iostream>

class Apple : public sf::Drawable
{
public:
	Apple(const sf::Color& color);    
	void appleCollision();
private:
	sf::RectangleShape apple;
	void updatePositionApple();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

