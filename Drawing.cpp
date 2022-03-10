#include <SFML/Graphics.hpp>

#include "Variables.h"

namespace Drawing {

	namespace {

		void draw_line(sf::RenderWindow& rw, sf::RectangleShape& ctx, Line line) {

		}

		void draw_obstacles(sf::RenderWindow& rw, std::vector<Obstacle>& obstacles) {

			// create shape & set Color Properties 
			sf::RectangleShape rs; 
			rs.setFillColor(sf::Color::Transparent); 
			rs.setOutlineThickness(3); 
			rs.setOutlineColor(sf::Color::Black); 


			// draw objects
			for (Obstacle& obj : obstacles) {

				rs.setPosition(obj.x, obj.y); 
				rs.setSize({ (float)obj.w, (float)obj.h });

				rw.draw(rs); 

			}

		}

	}

	void draw_screen(sf::RenderWindow& rw, Player& player, std::vector<Obstacle>& obstacles) {

		rw.clear(sf::Color::White); 
		
		rw.draw(player.shape); 

		draw_obstacles(rw, obstacles); 

		rw.display(); 

	}
	

}