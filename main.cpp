#include "SFML/Graphics.hpp"

#include <iostream>
#include "Map.h"
#include "Snake.h"


int main()
{
	srand(time(NULL));
	system("chcp 1250");
	system("cls");

	const unsigned window_width = 1280;
	const unsigned window_height = 700;
	sf::RenderWindow AppWindow(sf::VideoMode(window_width, window_height), "Fajno");
	
	sf::Event event;
	sf::Clock clock;

	sf::Font font;
	if (!font.loadFromFile("ArialCEBold.ttf"))
	{
		std::cout << "Problem with loading font!\n";
	}
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(20);
	std::string text_content = "F - STOP SNAKE\nR - RESTART\nG - ADD SCORE\nSCORE: ";

	// 1 second = 100 miliseconds = 1'000'000 microseconds
	const unsigned int animation_frame_duration = 16'600; // microseconds
	const unsigned int logic_frame_duration = 4'000;
	const unsigned int snake_frame_duration = 120'000;

	unsigned long long animation_frame_time{};
	unsigned long long logic_frame_time{};
	unsigned long long snake_frame_time{};
	unsigned long long current_program_time{}; // current time of all frames

	const sf::Vector2f map_size { 600, 200 };
	const sf::Vector2f map_position {500, 50};
	const sf::Vector2f snake_size {20, 20};

	// Lambda function 
	auto checkProportions = [](const sf::Vector2f& map_size, const sf::Vector2f& head_size) -> bool
	{
		if (static_cast<int>(map_size.x) % static_cast<int>(head_size.x) != 0
			||
			static_cast<int>(map_size.y) % static_cast<int>(head_size.y) != 0)
		{
			return false;
		}
		return true;
	};

	if (checkProportions(map_size, snake_size) == false)
	{
		std::cout << "You've entered incorrect proportions of snake head to map size.\n";
		return 0;
	}
	int snake_part_length = (map_size.x / snake_size.x) * (map_size.y / snake_size.y);
	Snake snake(snake_size, snake_part_length, map_position, map_size);
	Map myMap(map_size, map_position, snake_size);
	//short fps{};


	while (AppWindow.isOpen()) // <------ MAIN LOOP
	{
		current_program_time = clock.getElapsedTime().asMicroseconds(); // liczenie czasu od poczatku programu
		while (current_program_time - logic_frame_time < logic_frame_duration)
		{
			// zapewnia �eby czas klatek obl. by� taki jaki zamierzony
			sf::sleep(sf::microseconds(1000)); 
			current_program_time = clock.getElapsedTime().asMicroseconds();
		}

		while (logic_frame_time + logic_frame_duration < current_program_time)
		{
			logic_frame_time += logic_frame_duration; // uzupe�nia czas klatek obliczeniowych
		}

		// std::cout << "FPS_O: " << 1000000 / (current_program_time - logic_frame_time) << "\n";
		// std::cout << "T_O: " << (current_program_time - animation_frame_time) / 1000 << " ms\n"; //FRAMETIME

		// ---------- LOGIC ----------
		if (current_program_time - snake_frame_time > snake_frame_duration)
		{
			snake.UpdatePosition();
			text.setString(text_content + std::to_string(snake.getScore()) + "\n" + snake.getHeadPosition());
			while (snake_frame_time + snake_frame_duration < current_program_time)
			{
				snake_frame_time += snake_frame_duration;
			}
		}

		snake.MapColission(); 
		/* 
			Kolizja zostanie wykryta wczesniej niz snake zostanie narysowany.
			Zostanie natomiast zmieniona jego pozycja , gdyz klatki 'logiczne' wykonuja sie wczesniej.
		*/

		snake.BodyColission();

		while (AppWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				AppWindow.close();
				return 0;
			}
			if (event.type == sf::Event::KeyPressed)
				snake.KeyEvent(event);
		}
		// ----------------------------
		current_program_time = clock.getElapsedTime().asMicroseconds();
		if (current_program_time - animation_frame_time > animation_frame_duration)
		{
			/*
				Skip drawing objects untill current program time catches animation_frame_duration.
				It helps do some logic while animation is skipped and also animation frames can be set.
			*/
			AppWindow.clear({ 20,0,0 });
			//	---- DRAWING ----
			AppWindow.draw(text);
			AppWindow.draw(myMap);
			AppWindow.draw(snake);
			//  -----------------
			AppWindow.display();

			// std::cout << "FPS_A: " << 1'000'000 / (current_program_time - animation_frame_time) << "\n"; // FRAMERATE
			// std::cout << "T_A: " << (current_program_time - animation_frame_time) / 1000 << " ms\n"; //FRAMETIME
			//fps = (current_program_time - animation_frame_time) / 1000;
			//text.setString("FRAMETIME A: " + std::to_string(fps) + " ms\nScore: " + std::to_string(snake.getScore()));

			while (animation_frame_time + animation_frame_duration < current_program_time)
			{
				animation_frame_time += animation_frame_duration; 
				/* 
					Makes sure that animation_frame_time is close to current_program time
					which then can be used to do substraction in if statement.
				*/
			}

		}
	}

	return 0;
}