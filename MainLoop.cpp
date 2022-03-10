#include <vector>

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

		Player player(screen_width / 2, screen_height / 2, 10); 

		init_SFML(window); 

		while (true) {

			Events::event_handler(window, player); 

			Calculations::calculate_frame(player); 

			Drawing::draw_screen(window, player); 

		}

	}

}


/*

Vector with Obstacles

Vector or Array with Rays

*/