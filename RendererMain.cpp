#include <iostream>

#include <vector>
#include <array>

#include <SFML/Graphics.hpp>

#include "Variables.h"
#include "RenderEvents.h"

namespace RendererMain {

	void run(Player& player, std::vector<Obstacle>& obstacles) {

		sf::RenderWindow window3D(sf::VideoMode(400, 300), "3D-View"); 

		while (window3D.isOpen()) {

			RenderEvents::event_handler(window3D); 



		}

	}

}