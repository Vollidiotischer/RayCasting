#include <iostream>
#include <vector>
#include <array>

#include <SFML/Graphics.hpp>

#include "Variables.h"


namespace Events {

	namespace {
		void evaluate_movement(sf::Event& events, Player& player, bool key_pressed) {

			// key_pressed:	if key_pressed is 1 then the key was pressed and the velocity is set
			//				if key_pressed is 0 then the key was released and the velocity is reset



			float veclocity = (float)key_pressed * player.speed; 

			switch (events.key.code) {
				case sf::Keyboard::Up:
					player.vy = -veclocity;
					break;
				case sf::Keyboard::Down:
					player.vy = veclocity;
					break;
				case sf::Keyboard::Right:
					player.vx = veclocity;
					break;
				case sf::Keyboard::Left:
					player.vx = -veclocity;
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

			// Up/Down/Right/Left Player Movement
			if (events.type == sf::Event::KeyPressed || events.type == sf::Event::KeyReleased) {
				evaluate_movement(events, player, events.type == sf::Event::KeyPressed);
			}

			// Object creation (Mouse Events) 
			if (events.type == sf::Event::MouseButtonPressed) {
				int x = sf::Mouse::getPosition(window).x; 
				int y = sf::Mouse::getPosition(window).y; 
				obstacles.push_back(Obstacle(x, y, 0, 0)); 
			}

			if (events.type == sf::Event::MouseButtonReleased) {
				obstacles.back().is_in_creation = false; 
				std::cout << "Obstacle: " << obstacles.back().x << " " << obstacles.back().y << " " << obstacles.back().w << " " << obstacles.back().h << std::endl;

			}
		}

	}

}