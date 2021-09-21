#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
namespace grid
{
	bool checkProportions(const sf::Vector2f& map_size,const sf::Vector2f& head_size);
}

class Snake : public sf::Drawable
{
public:
	Snake(const sf::Vector2f& head_size, const int& part_len, const sf::Vector2f& map_pos, const sf::Vector2f& map_size);
	~Snake();
	void snakeRotation(const sf::Event& event);
	void snakeMovement();
	void snakeMapColission();
	void snakeBodyColission();
	unsigned short getScore();

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	// ---- Initialization list order ----
	const int part_len;
	sf::Vector2f move;
	sf::Vector2f snake_size;
	sf::Vector2f* last_part_position;
	sf::RectangleShape* snake_part;
	unsigned short score;
	sf::Vector2f map_pos;
	sf::Vector2f map_size;
	// -------------------------------------

	// --- SnakeHead Class ---
	class CSnakeHead : public sf::Drawable, public sf::Transformable
	{
	public:
		CSnakeHead(const sf::Vector2f& h_size, const sf::Vector2f& t_size);
		void setSizeHead(const sf::Vector2f& h_size);
		void setFillColorHead(const sf::Color& h_color);
		
		void setSizeTongue(const sf::Vector2f& t_size);
		void setFillColorTongue(const sf::Color& t_color);

	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		sf::RectangleShape head;
		sf::RectangleShape tongue;
	};
	// ------------------------

	CSnakeHead snake_head;
};