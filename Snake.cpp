#include "Snake.h"

Snake::Snake(const sf::Vector2f& head_size, const int& part_len, const sf::Vector2f& map_pos, const sf::Vector2f& map_size)
	: part_quantity(part_len), move{ 0.f, 0.f }, head_size(head_size),
	 score(0), map_pos(map_pos), map_size(map_size),
	snake_head({ head_size }, { head_size.x / 7.f, head_size.y / 1.5f }), is_collided(false)
{
	snake_head.setOrigin(head_size / 2.f);
	snake_head.setFillColorHead(sf::Color::Red);
	snake_head.setFillColorTongue(sf::Color(0, 128, 0, 230));

	snake_part_vertices.reserve(part_quantity * 4); // times 4 for all vertices 
	last_part_position.reserve(part_quantity * 4);

	for (int i = 0; i < 8; i++)
	{
		snake_part_vertices.emplace_back();
		last_part_position.emplace_back();
		snake_part_vertices[i].color = sf::Color(sf::Color(255, 128, 0, 220));
	}

	/*
	snake_part_vertices[0].color = sf::Color::Red;
	snake_part_vertices[1].color = sf::Color::Yellow;
	snake_part_vertices[2].color = sf::Color::Yellow;
	snake_part_vertices[3].color = sf::Color::Red;

	snake_part_vertices[4].color = sf::Color::Yellow;
	snake_part_vertices[5].color = sf::Color::Red;
	snake_part_vertices[6].color = sf::Color::Red;
	snake_part_vertices[7].color = sf::Color::Yellow;
	*/

	this->defaultSnakePos();

	// When substracting from Y coord you will move up in XY plane not down...

	/*
	1 2
	0 3 1 2
		0 3 5 6
			4 7
	*/
	return;

}
Snake::~Snake()
{
	return;
}

void Snake::KeyEvent(const sf::Event& event)
{
	float wanted_rotation{};
	sf::Vector2f wanted_move{};

	static sf::Vector2f last_position{};

	switch (event.key.code)
	{
	case sf::Keyboard::Up:
	{
		wanted_rotation = 0.f;
		wanted_move = { 0.f, -head_size.y };
		break;
	}
		
	case sf::Keyboard::Left:
	{
		wanted_rotation = 270.f;
		wanted_move = { -head_size.x, 0.f };
		break;
	}

	case sf::Keyboard::Down:
	{
		wanted_rotation = 180.f;
		wanted_move = { 0.f, head_size.y };
		break;
	}

	case sf::Keyboard::Right:
	{
		wanted_rotation = 90.f;
		wanted_move = { head_size.x, 0.f };
		break;
	}

	case sf::Keyboard::F:
	{
		move = { 0.f , 0.f };
		last_position = { 0.f, 0.f };
		return;
	}
	case sf::Keyboard::G:
	{
		if (score < part_quantity)
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
		rotateHeadVertices(static_cast<int>(wanted_rotation));
		move = wanted_move;
		last_position = snake_head.getPosition();
	}
	return;
}

void Snake::UpdatePosition()
{
	if (move != sf::Vector2f{ 0.f, 0.f } && !is_collided)
	{
		for (unsigned i = 0; i < 4; i++)
		{
			last_part_position[i] = snake_head_vertices[i]; 
			// Giving last_part_position current head_position
			// Only for one element behind the head
		}
		for (unsigned i = 4, j = 0; i < last_part_position.size() && j < snake_part_vertices.size(); i++, j++)
		{
			last_part_position[i] = snake_part_vertices[j].position;
		}

		snake_head.move(move);
		// Moving head
		
		for (unsigned i = 0; i < 4; i++)
		{
			snake_head_vertices[i] += move; 
		}
		for (unsigned i = 0; i < snake_part_vertices.size(); i++)
		{
			snake_part_vertices[i].position = last_part_position[i];
			// Giving current part_vertices previous position of head and other parts
		}
	}

	return;
}

void Snake::MapColission()
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
} // HEY sproboj uzyc jezyka jako collider bo on troche wystaje i moze by siadlo

void Snake::BodyColission()
{

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

	float ax = 0.5 * snake_head.getHeadSize().x;
	float ay = 0.5 * snake_head.getHeadSize().y;
	float sx = snake_head.getPosition().x;
	float sy = snake_head.getPosition().y;

	snake_head_vertices[0] = { sx - ax, sy + ax };
	snake_head_vertices[1] = { sx - ax, sy - ax };
	snake_head_vertices[2] = { sx + ax, sy - ax };
	snake_head_vertices[3] = { sx + ax, sy + ax };

	if (snake_part_vertices.size() > 8) // size - returns number of elements
	{
		snake_part_vertices.erase(snake_part_vertices.begin() + 6, snake_part_vertices.begin() + 6 + score * 4);
		last_part_position.erase(last_part_position.begin() + 6, last_part_position.begin() + 6 + score * 4);
	}

	snake_part_vertices[0].position = { snake_head_vertices[1].x, snake_head_vertices[1].y + 2 * snake_head.getHeadSize().y };
	snake_part_vertices[1].position = snake_head_vertices[0];
	snake_part_vertices[2].position = snake_head_vertices[3];
	snake_part_vertices[3].position = { snake_head_vertices[2].x, snake_head_vertices[2].y + 2 * snake_head.getHeadSize().y };

	snake_part_vertices[4].position = { snake_head_vertices[1].x, snake_head_vertices[1].y + 3 * snake_head.getHeadSize().y };
	snake_part_vertices[5].position = snake_part_vertices[0].position;
	snake_part_vertices[6].position = snake_part_vertices[3].position;
	snake_part_vertices[7].position = { snake_head_vertices[2].x, snake_head_vertices[2].y + 3 * snake_head.getHeadSize().y };

	score = 0;
	return;
}

void Snake::rotateHeadVertices(const int& angle)
{
	float ax = 0.5 * head_size.x;
	float ay = 0.5 * head_size.y;
	float sx = snake_head.getPosition().x;
	float sy = snake_head.getPosition().y;

	switch (angle)
	{
	case 0: // UP
	{
		snake_head_vertices[0] = { sx - ax, sy + ax };
		snake_head_vertices[1] = { sx - ax, sy - ax };
		snake_head_vertices[2] = { sx + ax, sy - ax };
		snake_head_vertices[3] = { sx + ax, sy + ax };
		break;
	}

	case 270: // LEFT
	{
		snake_head_vertices[0] = { sx + ax, sy + ax };
		snake_head_vertices[1] = { sx - ax, sy + ax };
		snake_head_vertices[2] = { sx - ax, sy - ax };
		snake_head_vertices[3] = { sx + ax, sy - ax };
		break;
	}

	case 180: // DOWN
	{
		snake_head_vertices[0] = { sx + ax, sy - ax };
		snake_head_vertices[1] = { sx + ax, sy + ax };
		snake_head_vertices[2] = { sx - ax, sy + ax };
		snake_head_vertices[3] = { sx - ax, sy - ax };
		break;
	}

	case 90: // RIGHT
	{
		snake_head_vertices[0] = { sx - ax, sy - ax };
		snake_head_vertices[1] = { sx + ax, sy - ax };
		snake_head_vertices[2] = { sx + ax, sy + ax };
		snake_head_vertices[3] = { sx - ax, sy + ax };
		break;
	}

	default:
		return;
	}

	return;
}

void Snake::addSnakePart()
{
	for (int i = 0; i < 4; i++)
	{
		snake_part_vertices.emplace_back();
		last_part_position.emplace_back();
	}

	for (int i = snake_part_vertices.size() - 4; i < snake_part_vertices.size(); i++)
	{
		snake_part_vertices[i].color = sf::Color(255, 128, 0, 220);
	}
	return;
}

void Snake::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(snake_head, states);
	target.draw(&snake_part_vertices[0], snake_part_vertices.size(), sf::Quads);
	return;
}

// ----------- SnakeHead Class ----------

Snake::CSnakeHead::CSnakeHead(const sf::Vector2f& h_size, const sf::Vector2f& t_size)
	: head(h_size), tongue(t_size)
{
	tongue.setOrigin(tongue.getSize() / 2.f);
	tongue.setPosition({ head.getSize().x / 2.f,  head.getSize().y / 4.f});
	// nie mo¿na ustawiæ pozycji g³owy bo head nie ma ustawionego rozmiaru
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

