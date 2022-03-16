#include <iostream>
#include <vector>
#include <array>

#include <SFML/Graphics.hpp>

#include "Variables.h"


namespace Events {

	namespace {

		void evaluate_rotation(sf::Event& events, Player& player, bool key_pressed) {

			float rottion_velocity = (float)key_pressed * player.rotation_speed;

			switch (events.key.code) {
				case sf::Keyboard::D:
					player.delta_angle = -rottion_velocity;
					break;
				case sf::Keyboard::F:
					player.delta_angle = rottion_velocity;
					break;
			}

		}

		void evaluate_movement(sf::Event& events, Player& player, bool key_pressed) {

			// key_pressed:	if key_pressed is 1 then the key was pressed and the velocity is set
			//				if key_pressed is 0 then the key was released and the velocity is reset



			float velocity = (float)key_pressed * player.speed; 

			float angle = (player.angle + player_view_range / 2.f) / 180 * 3.1415; 

			switch (events.key.code) {
				case sf::Keyboard::Up:
					player.vy = sin(angle) * velocity;
					player.vx = cos(angle) * velocity;
					break;
				case sf::Keyboard::Down:
					player.vy = -sin(angle) * velocity;
					player.vx = -cos(angle) * velocity;
					break;
				case sf::Keyboard::Left:
					angle -= 3.1415 / 2.f; 
					player.vy = sin(angle) * velocity;
					player.vx = cos(angle) * velocity;
					break;
				case sf::Keyboard::Right:
					angle += 3.1415 / 2.f;
					player.vy = sin(angle) * velocity;
					player.vx = cos(angle) * velocity;
					break;

			}

		}
	}

	void event_handler(sf::RenderWindow& window, Player& player, std::vector<Obstacle>& obstacles) {

		sf::Event events; 

		while (window.pollEvent(events)) {
			
			// Window close Event
			if (events.type == sf::Event::Closed) {
				window.close(); 
			}

			if (events.type == sf::Event::KeyPressed) {
				if (events.key.code == sf::Keyboard::Space) {
					player.toggel_control_mode(); 
				}
			}


			// player Movement & rotation
			if (events.type == sf::Event::KeyPressed || events.type == sf::Event::KeyReleased) {
				if (player.is_controlled_by_keyboard) {
					evaluate_movement(events, player, events.type == sf::Event::KeyPressed);
				}

				evaluate_rotation(events, player, events.type == sf::Event::KeyPressed);
			}

			if (!player.is_controlled_by_keyboard) {
				player.x = sf::Mouse::getPosition(window).x;
				player.y = sf::Mouse::getPosition(window).y;

			}

			// Object creation (Mouse Events) 
			if (events.type == sf::Event::MouseButtonPressed) {
				int x = sf::Mouse::getPosition(window).x;
				int y = sf::Mouse::getPosition(window).y;

				// Right Mouse -> line
				// Left Mouse -> Rect 

				obstacles.push_back(Obstacle(x, y, 0, 0, events.key.code == sf::Mouse::Left));

			}

			if (events.type == sf::Event::MouseButtonReleased) {
				obstacles.back().is_in_creation = false;
				std::cout << "Obstacle: " << obstacles.back().x << " " << obstacles.back().y << " " << obstacles.back().w << " " << obstacles.back().h << std::endl;

			}
		}

	}

}