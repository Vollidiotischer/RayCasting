
#include <SFML/Graphics.hpp>

#include "Variables.h"



namespace RenderDrawing {

	namespace {
		
		void draw_vision(sf::RenderWindow& rw, Player& player) {

			float height_factor = (float)screen_height_3d / (float)default_ray_length;

			float ray_thickness = (float)screen_width_3d / (float)num_rays;

			sf::RectangleShape rect({ ray_thickness, 0.f });

			for (int i = 0; i < num_rays; i++) {

				float x = i * ray_thickness;

				float height = screen_height_3d * 50 / player.rays[i].length;
				height = height > screen_height_3d ? screen_height_3d : height; 

				float rest_height = (screen_height_3d - height) / 2.f;

				// top
				rect.setPosition({ x, 0 });
				rect.setSize({ ray_thickness, rest_height });
				rect.setFillColor(sf::Color::Black);
				rw.draw(rect);

				// Bottom
				rect.setPosition({ x, height + rest_height });
				rect.setSize({ ray_thickness, rest_height });
				rw.draw(rect);




				// Middle
				float color_factor = 255 * (height / screen_height_3d);
				rect.setPosition({ x, rest_height });
				rect.setSize({ ray_thickness, height });
				rect.setFillColor(sf::Color(color_factor, color_factor, color_factor));
				rw.draw(rect);



			}
		}

	}

	void draw_screen(sf::RenderWindow& rw, Player& player) {

		rw.clear(sf::Color::Black); 

		draw_vision(rw, player);

		rw.display(); 

	}

}