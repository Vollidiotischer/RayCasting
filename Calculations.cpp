#include <iostream>
#include <vector>
#include <array>

#include <SFML/Graphics.hpp>

#include "Variables.h"

namespace Calculations {

	namespace {

		float find_min_lambda_range(float arr[5]) {

			float minimum = 1.0;

			for (int i = 0; i < 5; i++) {
				if (arr[i] >= 0 && arr[i] < minimum) {
					minimum = arr[i];
				}
			}

			return minimum;

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

		void calculate_ray_length(std::vector<Obstacle>& obstacles, Player& player) {

			/*
			SQUARE: 
				Ray: (x, y) + lambda * (dx, dy)

				Obstacle (o): consists of 4 vectors (The 4 Sides of the Square) 
					R1: (o.x, o.y) + lambda_2 * (o.w, 0)		[Top]
					R2: (o.x, o.y) + lambda_2 * (0, o.h)		[Left]
					R3: (0.x + 0.w, o.y) + lambda_2 * (0, o.h)	[Right]
					R4: (o.x, o.y + o.h) + lambda_2 * (o.w, 0)	[Bottom]

				Calculate Intersection between the ray and each side of an obstacle 
					-> lambda_rx_1 => how long the ray has to be
					-> lambda_rx_2 => if the ray hits the side (and the intersection is not outside of [0, 1]) 
						-> if lambda_rx_2 is not in [0, 1] then lambda_rx_1 is invalid
			
			*/

			for (int i = 0; i < player.rays.size(); i++) {

				player.rays[i].set_length(default_ray_length);

				float min_lambda = 1.0;

				for (int i2 = 0; i2 < obstacles.size(); i2++) {

					Ray& r = player.rays[i]; 
					Obstacle& o = obstacles[i2];

					if (obstacles[i2].is_rect) {

						// Ray = R1 [Top] 
						float lambda_r1_1 = (obstacles[i2].y - player.rays[i].y) / player.rays[i].dy;
						float lambda_r1_2 = (player.rays[i].x - obstacles[i2].x + lambda_r1_1 * player.rays[i].dx) / obstacles[i2].w;
						lambda_r1_1 = lambda_r1_2 >= 0 && lambda_r1_2 <= 1.0 ? lambda_r1_1 : 1.0;

						// Ray = R2 [Left]
						float lambda_r2_1 = (obstacles[i2].x - player.rays[i].x) / player.rays[i].dx;
						float lambda_r2_2 = (player.rays[i].y - obstacles[i2].y + lambda_r2_1 * player.rays[i].dy) / obstacles[i2].h;
						lambda_r2_1 = lambda_r2_2 >= 0 && lambda_r2_2 <= 1.0 ? lambda_r2_1 : 1.0;

						// Ray = R3 [Right]
						float lambda_r3_1 = (obstacles[i2].x + obstacles[i2].w - player.rays[i].x) / player.rays[i].dx;
						float lambda_r3_2 = (player.rays[i].y - obstacles[i2].y + lambda_r3_1 * player.rays[i].dy) / obstacles[i2].h;
						lambda_r3_1 = lambda_r3_2 >= 0 && lambda_r3_2 <= 1.0 ? lambda_r3_1 : 1.0;

						// Ray = R4 [Bottom]
						float lambda_r4_1 = (obstacles[i2].y + obstacles[i2].h - player.rays[i].y) / player.rays[i].dy;
						float lambda_r4_2 = (player.rays[i].x - obstacles[i2].x + lambda_r4_1 * player.rays[i].dx) / obstacles[i2].w;
						lambda_r4_1 = lambda_r4_2 >= 0 && lambda_r4_2 <= 1.0 ? lambda_r4_1 : 1.0;


						// get the smallest lambda -> first obstacle hit 
						float lambdas[] = { lambda_r1_1, lambda_r2_1, lambda_r3_1, lambda_r4_1, min_lambda };
						min_lambda = find_min_lambda_range(lambdas);

					}
					else {

						//float lambda_1 = (o.h * o.x - o.y * o.w - o.h * r.x + o.w * r.y) / (r.dx * o.h - r.dy * o.w);	  //	[WWW]
						float lambda_2 = (r.dy * o.x - r.dx * o.y - r.dy * r.x + r.dx * r.y) / (r.dx * o.h - r.dy * o.w); //	[WWW]

						//float lambda_2 = ((o.h - r.y) * r.dx + (r.x - o.x) * r.dy) / (o.w * r.dy - o.h * r.dx); 

						float lambda_1 = (o.x - r.x + lambda_2 * o.w) / r.dx;

						if (lambda_2 >= 0 && lambda_2 <= 1 && lambda_1 < min_lambda && lambda_1 >= 0) {
							min_lambda = lambda_1; 
						}
					}
				}


				if (min_lambda < 1) {
					player.rays[i].set_length(player.rays[i].length * min_lambda);
				}

			}

		}

	}

	void calculate_frame(sf::RenderWindow& rw, Player& player, std::vector<Obstacle>& obstacles) {


		// Delta time
		static sf::Clock clock; 
		static float old_time; 
		float delta = (clock.getElapsedTime().asMicroseconds() - old_time) / 1000.0; 
		old_time = clock.getElapsedTime().asMicroseconds(); 

		player.advance_position(delta); 

		update_obstacles_in_creation(rw, obstacles); 

		calculate_ray_length(obstacles, player); 

	}

}