#include <vector>

#include <SFML/Graphics.hpp>

#include "Variables.h"

namespace Calculations {

	namespace {
		void update_player(Player& player) {

			player.x += player.vx; 
			player.y += player.vy; 

			player.update_position(); 
		}

		void update_obstacles_in_creation(sf::RenderWindow& rw, std::vector<Obstacle>& obstacles) {

			if (obstacles.size() == 0) {
				return; 
			}

			Obstacle& obj = obstacles.back(); 

			if (obj.is_in_creation) {
				int x = sf::Mouse::getPosition(rw).x; 
				int y = sf::Mouse::getPosition(rw).y; 

				int dx = x - obj.x; 
				int dy = y - obj.y;

				obj.w = dx; 
				obj.h = dy; 
			}
		}
	}

	void calculate_frame(sf::RenderWindow& rw, Player& player, std::vector<Obstacle>& obstacles) {

		update_player(player); 

		update_obstacles_in_creation(rw, obstacles); 


	}

}