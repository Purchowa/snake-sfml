#pragma once
#include <iostream>
#include <cmath>
#include <vector>
#include "SFML/Graphics.hpp"
#include "Vector2Overload.h"

class Ray : public sf::Drawable, public sf::Transformable
{
public:
	Ray(const int count, const float length, const sf::Vector2f origin);
	sf::Vertex& operator[](const int index);

private:
	std::vector<sf::Vertex> Rays;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

