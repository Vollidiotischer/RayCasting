#include <iostream>
#include <vector>
#include <array>

#include <SFML/Graphics.hpp>

#include "Variables.h"
#include "Events.h"
#include "Calculations.h"
#include "Drawing.h"



namespace MainLoop {

	namespace {
		void init_SFML(sf::RenderWindow& rw) {

			rw.setKeyRepeatEnabled(false);
		}
	}

	void run() {

		sf::RenderWindow window(sf::VideoMode(screen_width, screen_height), "Ray Casting");

		Player player(screen_width / 2, screen_height / 2, 15, 0.15); 

		std::vector<Obstacle> obstacles; 

		init_SFML(window); 
		
		while (window.isOpen()) {

			Events::event_handler(window, player, obstacles); 

			Calculations::calculate_frame(window, player, obstacles); 

			Drawing::draw_screen(window, player, obstacles); 
			
		}

	}

}
