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

			rw.setPosition({ 150, 100 });

			rw.requestFocus(); 

			rw.setKeyRepeatEnabled(false);
		}
	}

	void run(Player& player, std::vector<Obstacle>& obstacles) {

		sf::RenderWindow window(sf::VideoMode(screen_width, screen_height), "Ray Casting", sf::Style::Close | sf::Style::Titlebar);

		init_SFML(window); 
		
		while (window.isOpen()) {

			Events::event_handler(window, player, obstacles); 

			Calculations::calculate_frame(window, player, obstacles); 

			Drawing::draw_screen(window, player, obstacles); 
			
		}

	}

}
