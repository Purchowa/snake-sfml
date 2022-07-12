#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"

std::ostream& operator<< (std::ostream & out, const sf::Vector2f vec);

// NOTE: It's array divison.
sf::Vector2f operator/(const sf::Vector2f& v1, const sf::Vector2f& v2);
