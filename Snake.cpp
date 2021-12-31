#include "Snake.h"

Snake::Snake(const sf::Vector2f& head_size, const int& part_len, const sf::Vector2f& map_pos, const sf::Vector2f& map_size)
	: VERTICES_NUMBER(4), PART_QUANTITY(part_len), SNAKE_PART_COLOR({ 255, 128, 0, 220 }),
	move{ 0.f, 0.f }, HEAD_SIZE(head_size),
	score(0), map_pos(map_pos), map_size(map_size),
	snake_head({ head_size }, { head_size.x / 7.f, head_size.y / 1.5f }), is_collided(false)
{
	snake_head.setOrigin(head_size / 2.f);
	snake_head.setFillColorHead(sf::Color::Red);
	snake_head.setFillColorTongue(sf::Color(0, 128, 0, 230));

	int part_capacity = PART_QUANTITY * VERTICES_NUMBER;
	part_vertices.reserve(part_capacity);
	last_part_position.reserve(part_capacity);

	for (int i = 0; i < 2 * VERTICES_NUMBER; i++)
	{
		part_vertices.emplace_back();
		last_part_position.emplace_back();
		part_vertices[i].color = SNAKE_PART_COLOR;
	}

	/*
	part_vertices[0].color = sf::Color::Red;
	part_vertices[1].color = sf::Color::Yellow;
	part_vertices[2].color = sf::Color::Yellow;
	part_vertices[3].color = sf::Color::Red;

	part_vertices[4].color = sf::Color::Yellow;
	part_vertices[5].color = sf::Color::Red;
	part_vertices[6].color = sf::Color::Red;
	part_vertices[7].color = sf::Color::Yellow;
	*/
	// When substracting from Y coord you will move up in XY plane not down...

	this->defaultSnakePos();

	this->initApple(sf::Color::Green);

	return;

}
Snake::~Snake()
{
	return;
}

void Snake::keyEvent(const sf::Event& event)
{
	float wanted_rotation{};
	sf::Vector2f wanted_move{};

	static sf::Vector2f last_position{};

	switch (event.key.code)
	{
	case sf::Keyboard::Up:
	{
		wanted_rotation = 0.f;
		wanted_move = { 0.f, -HEAD_SIZE.y };
		break;
	}
		
	case sf::Keyboard::Left:
	{
		wanted_rotation = 270.f;
		wanted_move = { -HEAD_SIZE.x, 0.f };
		break;
	}

	case sf::Keyboard::Down:
	{
		wanted_rotation = 180.f;
		wanted_move = { 0.f, HEAD_SIZE.y };
		break;
	}

	case sf::Keyboard::Right:
	{
		wanted_rotation = 90.f;
		wanted_move = { HEAD_SIZE.x, 0.f };
		break;
	}

	case sf::Keyboard::S:
	{
		/*
			If last_position wasn't set to 0, snake wouldn't move afeter stop.
		*/
		move = { 0.f , 0.f };
		last_position = { 0.f, 0.f };
		return;
	}
	case sf::Keyboard::G:
	{
		if (score < PART_QUANTITY)
		{
			addSnakePart();
			score++;
		}
		return;
	}
	case sf::Keyboard::R:
	{
		is_collided = false;
		this->defaultSnakePos();
		move = { 0.f, 0.f };
		last_position = { 0.f, 0.f };
		snake_head.setRotation(0.f);

		return;
	}
	default:
	{
		std::cout << "Wrong key!\n";
		return;
	}
	}
	if (abs(wanted_rotation - snake_head.getRotation()) != 180.f && last_position != snake_head.getPosition())
	{
		snake_head.setRotation(wanted_rotation);
		// rotateHeadVertices(static_cast<int>(wanted_rotation)); <-- Not needed in static colors of parts and head
		move = wanted_move;
		last_position = snake_head.getPosition();
	}
	return;
}

void Snake::updatePositionSnake()
{
	if (move != sf::Vector2f{ 0.f, 0.f } && !is_collided)
	{
		for (unsigned i = 0; i < VERTICES_NUMBER; i++)
		{
			last_part_position[i] = head_vertices[i]; 
			// Assigning to last_part_position, current head_position
			// Only for one part behind the head
		}
		for (unsigned i = VERTICES_NUMBER, j = 0; i < last_part_position.size() && j < part_vertices.size(); i++, j++)
		{
			last_part_position[i] = part_vertices[j].position;
		}

		snake_head.move(move);
		// Moving head
		
		for (unsigned i = 0; i < VERTICES_NUMBER; i++)
		{
			head_vertices[i] += move; 
		}
		for (unsigned i = 0; i < part_vertices.size(); i++)
		{
			part_vertices[i].position = last_part_position[i];
			// Giving current part_vertices previous position of head and other parts
		}
	}

	return;
}

void Snake::mapColission()
{
	if (snake_head.getPosition().x < map_pos.x + 10|| 
		snake_head.getPosition().x > map_pos.x + map_size.x ||
		snake_head.getPosition().y < map_pos.y || 
		snake_head.getPosition().y > map_pos.y + map_size.y
		)
	{
		is_collided = true;

		return;
	}

	return;
}

void Snake::bodyColission()
{
	/*
		Starting from 8th index because collision can't happen on first two parts
	*/
	for (unsigned i = 2 * VERTICES_NUMBER; i < part_vertices.size(); i += VERTICES_NUMBER)
	{
		if (Snake::shapeContaintsPoint(&part_vertices[i], snake_head.getPosition()))
		{
			move = { 0.f, 0.f };
			return;
		}
	}
	return;
}

void Snake::appleCollision()
{
	if (snake_head.getPosition() == apple.getPosition())
	{
		std::cout << apple.getPosition().x << "\n";
	}
	return;
}

unsigned int Snake::getScore() const
{
	return score;
}

std::string Snake::getHeadPosition() const
{
	return "X: " + std::to_string(static_cast<int>(snake_head.getPosition().x))
		+ " Y: " + std::to_string(static_cast<int>(snake_head.getPosition().y)) + "\n";
}

void Snake::defaultSnakePos()
{
	snake_head.setPosition({
		(this->map_size.x / 2 + this->map_pos.x + snake_head.getOrigin().x),
		(this->map_size.y / 2 + this->map_pos.y + snake_head.getOrigin().y)

		});

	float ax = 0.5 * HEAD_SIZE.x;
	float ay = 0.5 * HEAD_SIZE.y;
	float sx = snake_head.getPosition().x;
	float sy = snake_head.getPosition().y;

	head_vertices[0] = { sx - ax, sy + ax };
	head_vertices[1] = { sx - ax, sy - ax };
	head_vertices[2] = { sx + ax, sy - ax };
	head_vertices[3] = { sx + ax, sy + ax };

	if (part_vertices.size() > (size_t)2 * VERTICES_NUMBER) // size - returns number of elements. Erasing past second part
	{
		std::vector <sf::Vertex>::iterator iter_part_vertices = part_vertices.begin() + 7;
		std::vector <sf::Vector2f>::iterator iter_part_pos = last_part_position.begin() + 7;
		// Begin returns iterator to 1st element. Adding 7 results in iterator to 8th element.

		part_vertices.erase(iter_part_vertices, iter_part_vertices + (size_t)score * VERTICES_NUMBER);
		last_part_position.erase(iter_part_pos, iter_part_pos + (size_t)score * VERTICES_NUMBER);
		// Erasing set -> [iterator, last_iterator) 
	}

	part_vertices[0].position = { head_vertices[1].x, head_vertices[1].y + 2 * HEAD_SIZE.y };
	part_vertices[1].position = head_vertices[0];
	part_vertices[2].position = head_vertices[3];
	part_vertices[3].position = { head_vertices[2].x, head_vertices[2].y + 2 * HEAD_SIZE.y };

	part_vertices[4].position = { head_vertices[1].x, head_vertices[1].y + 3 * HEAD_SIZE.y };
	part_vertices[5].position = part_vertices[0].position;
	part_vertices[6].position = part_vertices[3].position;
	part_vertices[7].position = { head_vertices[2].x, head_vertices[2].y + 3 * HEAD_SIZE.y };

	score = 0;
	return;
}

void Snake::rotateHeadVertices(const int& angle)
{
	float ax = 0.5 * HEAD_SIZE.x;
	float ay = 0.5 * HEAD_SIZE.y;
	float sx = snake_head.getPosition().x;
	float sy = snake_head.getPosition().y;

	switch (angle)
	{
	case 0: // UP
	{
		head_vertices[0] = { sx - ax, sy + ax };
		head_vertices[1] = { sx - ax, sy - ax };
		head_vertices[2] = { sx + ax, sy - ax };
		head_vertices[3] = { sx + ax, sy + ax };
		break;
	}

	case 270: // LEFT
	{
		head_vertices[0] = { sx + ax, sy + ax };
		head_vertices[1] = { sx - ax, sy + ax };
		head_vertices[2] = { sx - ax, sy - ax };
		head_vertices[3] = { sx + ax, sy - ax };
		break;
	}

	case 180: // DOWN
	{
		head_vertices[0] = { sx + ax, sy - ax };
		head_vertices[1] = { sx + ax, sy + ax };
		head_vertices[2] = { sx - ax, sy + ax };
		head_vertices[3] = { sx - ax, sy - ax };
		break;
	}

	case 90: // RIGHT
	{
		head_vertices[0] = { sx - ax, sy - ax };
		head_vertices[1] = { sx + ax, sy - ax };
		head_vertices[2] = { sx + ax, sy + ax };
		head_vertices[3] = { sx - ax, sy + ax };
		break;
	}

	default:
		return;
	}

	return;
}

void Snake::addSnakePart()
{ 
	// Adding 4 elements at the end of vector
	for (int i = 0; i < VERTICES_NUMBER; i++)
	{
		part_vertices.emplace_back();
		last_part_position.emplace_back();
	}

	// Giving them color
	for (int i = part_vertices.size() - VERTICES_NUMBER; i < part_vertices.size(); i++)
	{
		part_vertices[i].color = SNAKE_PART_COLOR;
	}
	return;
}

bool Snake::shapeContaintsPoint(const sf::Vertex quad[], const sf::Vector2f& point) const
{
	sf::Vector2f center{ 
		(quad[0].position.x + quad[2].position.x) * 0.5f,
		(quad[0].position.y + quad[2].position.y) * 0.5f
	};

	if (point == center)
		return true;

	return false;
}

void Snake::initApple(const sf::Color& apple_color)
{
	sf::Vector2i randApple{
		rand() % static_cast<int>(map_size.x / HEAD_SIZE.x),
		rand() % static_cast<int>(map_size.y / HEAD_SIZE.y)
	};
	apple.setOrigin(snake_head.getOrigin());
	apple.setPosition(
		{randApple.x * HEAD_SIZE.x + map_pos.x + snake_head.getOrigin().x},
		{randApple.y * HEAD_SIZE.y + map_pos.y + snake_head.getOrigin().y}
	);
	apple.setFillColor(apple_color);
	apple.setSize(HEAD_SIZE);

}

void Snake::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(snake_head, states);
	target.draw(&part_vertices[0], part_vertices.size(), sf::Quads);
	target.draw(apple);
	return;
}

// ----------- SnakeHead Class ----------

Snake::CSnakeHead::CSnakeHead(const sf::Vector2f& h_size, const sf::Vector2f& t_size)
	: head(h_size), tongue(t_size) // setting SIZE with constructor.
{
	tongue.setOrigin(tongue.getSize() / 2.f);
	tongue.setPosition({ head.getSize().x / 2.f,  head.getSize().y / 4.f});
}

void Snake::CSnakeHead::setSizeHead(const sf::Vector2f& h_size)
{
	head.setSize(h_size);
}

void Snake::CSnakeHead::setFillColorHead(const sf::Color& h_color)
{
	head.setFillColor(h_color);
}

void Snake::CSnakeHead::setSizeTongue(const sf::Vector2f& t_size)
{
	tongue.setSize(t_size);
}

void Snake::CSnakeHead::setFillColorTongue(const sf::Color& t_color)
{
	tongue.setFillColor(t_color);
}

sf::Vector2f Snake::CSnakeHead::getHeadSize() const
{
	return head.getSize();
}

void Snake::CSnakeHead::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform.combine(getTransform());
	// It combines earlier states of transformation with current ones.
	// states.transform *= getTransform(); // Operator '*=' was overloaded
	target.draw(head, states);
	target.draw(tongue, states);
}

// ----------------------------------------

