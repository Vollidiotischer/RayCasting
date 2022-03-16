
#include <SFML/Graphics.hpp>

#include "Variables.h"



namespace RenderDrawing {

	namespace {
		
		void draw_temp(sf::RenderWindow& rw, Player& player) {

			float height_factor = (float)screen_height_3d / (float)default_ray_length;

			float ray_thickness = (float)screen_width_3d / (float)num_rays;

			sf::RectangleShape rect({ ray_thickness, 0.f });

			for (int i = 0; i < num_rays; i++) {
				float y = 0;

				float x = i * ray_thickness;

				float height = screen_height_3d - player.rays[i].length;

				float rest_height = (screen_height_3d - height) / 2.f;

				// Top Bar
				rect.setPosition({ x, y });
				rect.setSize({ ray_thickness, rest_height });
				rect.setFillColor(sf::Color::Black);
				rw.draw(rect);

				// Middel Bar
				y += rest_height;

				rect.setPosition({ x, y });
				rect.setSize({ ray_thickness, height });
				rect.setFillColor(sf::Color::White);
				rw.draw(rect);

				// Bottom Bar
				y += height;

				rect.setPosition({ x, y });
				rect.setSize({ ray_thickness, rest_height });
				rect.setFillColor(sf::Color::Black);
				rw.draw(rect);

			}
		}

	}

	void draw_screen(sf::RenderWindow& rw, Player& player) {

		rw.clear(sf::Color::Black); 

		draw_temp(rw, player); 

		rw.display(); 

	}

}