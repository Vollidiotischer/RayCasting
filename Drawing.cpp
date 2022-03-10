#include <SFML/Graphics.hpp>

#include "Variables.h"

namespace Drawing {

	namespace {

		void draw_line(sf::RenderWindow& rw, sf::RectangleShape& ctx, Line line) {

		}

	}

	void draw_screen(sf::RenderWindow& rw, Player& player) {

		rw.clear(sf::Color::White); 
		
		rw.draw(*player.shape); 

		rw.display(); 

	}
	

}