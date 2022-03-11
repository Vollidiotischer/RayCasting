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