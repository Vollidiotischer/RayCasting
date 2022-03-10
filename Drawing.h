#pragma once


namespace Drawing {

	namespace {

		void draw_line(sf::RenderWindow&, sf::RectangleShape&, Line);

	}

	void draw_screen(sf::RenderWindow&, Player&, std::vector<Obstacle>&); 

}