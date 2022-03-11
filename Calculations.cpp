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

			for (int i = 0; i < player.rays.size(); i++) {

				player.rays[i].set_length(1000);

				float min_lambda = 1.0;

				for (int i2 = 0; i2 < obstacles.size(); i2++) {

					float lambda_r1_1 = (obstacles[i2].y - player.rays[i].y) / player.rays[i].dy;
					float lambda_r1_2 = (player.rays[i].x - obstacles[i2].x + lambda_r1_1 * player.rays[i].dx) / obstacles[i2].w;
					lambda_r1_1 = lambda_r1_2 >= 0 && lambda_r1_2 <= 1.0 ? lambda_r1_1 : 1.0; 

					float lambda_r2_1 = (obstacles[i2].x - player.rays[i].x) / player.rays[i].dx;
					float lambda_r2_2 = (player.rays[i].y - obstacles[i2].y + lambda_r2_1 * player.rays[i].dy) / obstacles[i2].h;
					lambda_r2_1 = lambda_r2_2 >= 0 && lambda_r2_2 <= 1.0 ? lambda_r2_1 : 1.0;

					float lambda_r3_1 = (obstacles[i2].x + obstacles[i2].w - player.rays[i].x) / player.rays[i].dx;
					float lambda_r3_2 = (player.rays[i].y - obstacles[i2].y + lambda_r3_1 * player.rays[i].dy) / obstacles[i2].h;
					lambda_r3_1 = lambda_r3_2 >= 0 && lambda_r3_2 <= 1.0 ? lambda_r3_1 : 1.0;

					float lambda_r4_1 = (obstacles[i2].y + obstacles[i2].h - player.rays[i].y) / player.rays[i].dy;
					float lambda_r4_2 = (player.rays[i].x - obstacles[i2].x + lambda_r4_1 * player.rays[i].dx) / obstacles[i2].w;
					lambda_r4_1 = lambda_r4_2 >= 0 && lambda_r4_2 <= 1.0 ? lambda_r4_1 : 1.0;


					float lambdas[] = { lambda_r1_1, lambda_r2_1, lambda_r3_1, lambda_r4_1, min_lambda }; 

					min_lambda = find_min_lambda_range(lambdas); 

				}


				if (min_lambda < 1) {
					player.rays[i].set_length(player.rays[i].length * min_lambda);
				}

			}

		}

	}

	void calculate_frame(sf::RenderWindow& rw, Player& player, std::vector<Obstacle>& obstacles) {

		static sf::Clock clock; 
		static float old_time; 
		float delta = (clock.getElapsedTime().asMicroseconds() - old_time) / 1000.0; 
		old_time = clock.getElapsedTime().asMicroseconds(); 

		player.advance_position(delta); 

		update_obstacles_in_creation(rw, obstacles); 

		player.update_ray_position(); 

		calculate_ray_length(obstacles, player); 

	}

}