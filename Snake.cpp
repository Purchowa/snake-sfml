#include "Snake.h"

Snake::Snake(const sf::Vector2f& head_size, const int& part_len, const sf::Vector2f& map_pos, const sf::Vector2f& map_size)
	: part_len(part_len), move{ 0.f, 0.f }, snake_size(head_size), last_part_position(new sf::Vector2f[part_len]),
	snake_part(new sf::RectangleShape[part_len]), score(2), map_pos(map_pos), map_size(map_size),
	snake_head({ head_size }, { head_size.x / 7.f, head_size.y / 1.5f })
{

	snake_head.setOrigin(head_size / 2.f);
	snake_head.setPosition({
		(this->map_size.x / 2 + this->map_pos.x + snake_head.getOrigin().x),
		(this->map_size.y / 2 + this->map_pos.y + snake_head.getOrigin().y)
		
		});
	snake_head.setFillColorHead(sf::Color::Red);
	snake_head.setFillColorTongue(sf::Color(0, 128, 0, 230));

	for (unsigned short i = 0; i < part_len; i++)
	{
		snake_part[i].setSize(head_size);
		snake_part[i].setOrigin(snake_head.getOrigin());
		snake_part[i].setFillColor(sf::Color(95, 122, 97, 220));
		last_part_position[i] = snake_part[i].getPosition();
		// initializaton of every last_part_position to currentposition of snake_part
	}

	snake_part[0].setPosition({ snake_head.getPosition().x, snake_head.getPosition().y + head_size.y * 1});
	snake_part[1].setPosition({ snake_head.getPosition().x, snake_head.getPosition().y + head_size.y * 2});

	return;

}

Snake::~Snake()
{
	delete [] last_part_position;
	delete [] snake_part;
	last_part_position = nullptr;
	snake_part = nullptr;

	return;
}

void Snake::snakeRotation(const sf::Event& event)
{
	float wanted_rotation{};
	sf::Vector2f wanted_move{};

	static sf::Vector2f last_position{};

	switch (event.key.code)
	{
	case sf::Keyboard::Up:
	{
		wanted_rotation = 0.f;
		wanted_move = { 0.f, -snake_size.y };
		break;
	}
		
	case sf::Keyboard::Left:
	{
		wanted_rotation = 270.f;
		wanted_move = { -snake_size.x, 0.f };
		break;
	}

	case sf::Keyboard::Down:
	{
		wanted_rotation = 180.f;
		wanted_move = { 0.f, snake_size.y };
		break;
	}

	case sf::Keyboard::Right:
	{
		wanted_rotation = 90.f;
		wanted_move = { snake_size.x, 0.f };
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
		if (score < part_len)
			score++;
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
		move = wanted_move;
		last_position = snake_head.getPosition();
	}
	return;
}

void Snake::snakeMovement()
{
	if (move != sf::Vector2f{ 0.f, 0.f })
	{
		for (unsigned short i = score - 1; i > 0; i--) // starting from last index
			last_part_position[i] = last_part_position[i - 1]; // shifting every position back
		last_part_position[0] = snake_head.getPosition(); // first "last_part_position" is current snake_head pos


		snake_head.move(move);

		for (unsigned short i = 0; i < score; i++)
			snake_part[i].setPosition(last_part_position[i]);
	}

	return;
}

void Snake::snakeMapColission()
{
	if (snake_head.getPosition().x < map_pos.x)
	{
		snake_head.setPosition({ snake_head.getPosition().x + map_size.x, snake_head.getPosition().y});
		return;
	}
	if (snake_head.getPosition().x > map_pos.x + map_size.x)
	{
		snake_head.setPosition({ snake_head.getPosition().x - map_size.x, snake_head.getPosition().y});
		return;
	}
	if (snake_head.getPosition().y < map_pos.y)
	{
		snake_head.setPosition({snake_head.getPosition().x, snake_head.getPosition().y + map_size.y });
		return;
	}
	if (snake_head.getPosition().y > map_pos.y + map_size.y)
	{
		snake_head.setPosition({ snake_head.getPosition().x, snake_head.getPosition().y - map_size.y });
		return;
	}
	return;
}

void Snake::snakeBodyColission()
{

	return;
}

unsigned short Snake::getScore()
{
	return score - 2;
}

void Snake::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(snake_head, states);
	for (unsigned short i = 0; i < score; i++)
		target.draw(snake_part[i], states);
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

void Snake::CSnakeHead::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform.combine(getTransform());
	// It combines earlier states of transformation with current ones.
	// states.transform *= getTransform(); // Operator '*=' was overloaded
	target.draw(head, states);
	target.draw(tongue, states);
}

// ----------------------------------------

bool grid::checkProportions(const sf::Vector2f& map_size, const sf::Vector2f& head_size)
{
	//True if proportions aren't correct.
	if (static_cast<int>(map_size.x) % static_cast<int>(head_size.x) != 0
		||
		static_cast<int>(map_size.y) % static_cast<int>(head_size.y) != 0)
	{
		return false;
	}
	return true;
}
