#include <iostream>

#include <SFML/Graphics.hpp>

#include "Variables.h"
#include "RenderEvents.h"
#include "RenderDrawing.h"

namespace RendererMain {

	void run(Player& player, std::vector<Obstacle>& obstacles) {

		sf::RenderWindow window3D(sf::VideoMode(screen_width_3d, screen_height_3d), "3D-View"); 

		while (window3D.isOpen()) {

			RenderEvents::event_handler(window3D); 

			RenderDrawing::draw_screen(window3D, player); 

		}

	}

}