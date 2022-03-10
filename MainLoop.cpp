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

		void init_rays(std::array<Ray, num_rays>& rays, Player& player) {

			for (int i = 0; i < num_rays; i++) {
				rays[i] = Ray(player.x, player.y, angle_between_rays * i, 0); 
			}

		}
	}

	void run() {

		sf::RenderWindow window(sf::VideoMode(screen_width, screen_height), "Ray Casting");

		Player player(screen_width / 2, screen_height / 2, 25, 0.07); 

		std::vector<Obstacle> obstacles; 

		std::array<Ray, num_rays> rays; 

		init_SFML(window); 

		init_rays(rays, player); 

		while (true) {

			Events::event_handler(window, player, obstacles); 

			Calculations::calculate_frame(window, player, obstacles); 

			Drawing::draw_screen(window, player, obstacles); 
			
		}

	}

}


/*

Todo: 
	fill ray struct 
	draw rays
	create ray data structure
		-> make it so that you can enter a ray density (probably with angle between each ray) 
	calculate ray length (RayCasting) 


Objects: 
	Vector with Obstacles
	Vector or Array with Rays

*/