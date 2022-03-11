#include <iostream>
#include <vector>
#include <array>

#include <SFML/Graphics.hpp>

#include "Variables.h"

namespace Drawing {

	namespace {

		void draw_ray(sf::RenderWindow& rw, sf::RectangleShape& ctx, Ray& ray) {

			ctx.setSize({ ray.length, 1 }); 
			ctx.setPosition(ray.x, ray.y); 
			ctx.setRotation(ray.angle); 

			rw.draw(ctx); 
		}

		void draw_obstacles(sf::RenderWindow& rw, std::vector<Obstacle>& obstacles) {

			// create shape & set Color Properties 
			sf::RectangleShape rs; 
			rs.setOutlineColor(sf::Color::Black); 
			

			// draw objects
			for (Obstacle& obj : obstacles) {
				if (obj.is_rect) {
					rs.setFillColor(sf::Color::Transparent);
					rs.setOutlineThickness(3);
					rs.setPosition(obj.x, obj.y);
					rs.setSize({ (float)obj.w, (float)obj.h });
					rs.setRotation(0); 
					rw.draw(rs);
				}
				else {
					rs.setFillColor(sf::Color::Black);
					rs.setOutlineThickness(1); 

					float length = sqrt((float)(obj.w * obj.w + obj.h * obj.h));
					float angle = acos(obj.w / length) * 180.0 / 3.1415 * (obj.h < 0 ? -1 : 1); 

					Ray temp_ray(obj.x, obj.y, angle, length); 
					temp_ray.adjust_direction(); 
					draw_ray(rw, rs, temp_ray); 

				}

			}

		}

		void draw_rays(sf::RenderWindow& rw, std::array<Ray, num_rays>& rays) {

			sf::RectangleShape ctx;

			ctx.setFillColor(sf::Color::Black);
			ctx.setOrigin(0, 1);
			
			for (Ray& r : rays) {
				draw_ray(rw, ctx, r); 
			}

		}

	}

	void draw_screen(sf::RenderWindow& rw, Player& player, std::vector<Obstacle>& obstacles) {

		rw.clear(sf::Color::White); 
		
		draw_rays(rw, player.rays);

		rw.draw(player.shape); 

		draw_obstacles(rw, obstacles); 

		rw.display(); 

	}
	

}