#include <SFML/Graphics.hpp>
#include "Variables.h"

namespace Events {

	namespace {
		void evaluate_movement(sf::Event& events, Player& player, bool key_pressed) {

			// key_pressed:	if key_pressed is 1 then the key was pressed and the velocity is set
			//				if key_pressed is 0 then the key was released and the velocity is reset



			float veclocity = (float)key_pressed * 0.05; 

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

	void event_handler(sf::RenderWindow& window, Player& player) {

		sf::Event events; 

		while (window.pollEvent(events)) {
			if (events.type == sf::Event::Closed) {
				window.close(); 
			}

			if (events.type == sf::Event::KeyPressed || events.type == sf::Event::KeyReleased) {
				evaluate_movement(events, player, events.type == sf::Event::KeyPressed);
			}
		}

	}

}