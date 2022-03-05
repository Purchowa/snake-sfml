#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include <vector>

class Snake : public sf::Drawable
{
public:
	Snake(const sf::Vector2f& head_size, const int& part_len, const sf::Vector2f& map_pos, const sf::Vector2f& map_size);
	void keyEvent(const sf::Event& event);
	void updatePositionSnake();
	void mapColission();
	void bodyColission();
	unsigned int getScore() const;
	std::string getHeadPosition() const;

private:
	void defaultSnakePos();
	void rotateHeadVertices(const int& angle);
	void addSnakePart();
	bool shapeContaintsPoint(const sf::Vertex quad[], const sf::Vector2f& point) const;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	// ---- Initialization list order ----
	const unsigned VERTICES_NUMBER;
	const unsigned PART_QUANTITY;
	const sf::Color SNAKE_PART_COLOR;
	const sf::Vector2f HEAD_SIZE;
	sf::Vector2f move;
	unsigned int score;
	sf::Vector2f map_pos;
	sf::Vector2f map_size;
	bool is_collided;
	// -------------------------------------

	sf::Vector2f head_vertices[4];
	std::vector<sf::Vector2f> last_part_position;
	std::vector<sf::Vertex> part_vertices;


	// --- SnakeHead Class ---
	class CSnakeHead : public sf::Drawable, public sf::Transformable
	{
	public:
		CSnakeHead(const sf::Vector2f& h_size, const sf::Vector2f& t_size);
		void setSizeHead(const sf::Vector2f& h_size);
		void setFillColorHead(const sf::Color& h_color);
		void setSizeTongue(const sf::Vector2f& t_size);
		void setFillColorTongue(const sf::Color& t_color);
		sf::Vector2f getHeadSize() const;

	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		sf::RectangleShape head;
		sf::RectangleShape tongue;
	};
	// ------------------------

	CSnakeHead snake_head;
};