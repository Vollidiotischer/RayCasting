#pragma once

#include <array>
#include <mutex>

#include <SFML/Graphics.hpp>


constexpr int screen_width = 750; 
constexpr int screen_height = 750;

constexpr int screen_width_3d = 900; 
constexpr int screen_height_3d = 506; 

constexpr float player_view_range = 75; // the players view angle-range in degrees

constexpr float angle_between_rays = 0.2; // in degrees 
constexpr int num_rays = player_view_range / angle_between_rays; 

constexpr int default_ray_length = 5000; 

struct Ray {
	int x, y; 
	float length, angle; 
	float dx = 0, dy = 0; 

	Ray() : x(0), y(0), length(default_ray_length), angle(0) {}

	Ray(int x, int y, float angle, float length = default_ray_length) : x(x), y(y), angle(angle), length(length) {
	
		adjust_direction(); 
	}

	void set_length(float new_length) {
		this->length = new_length;

		adjust_direction(); 
	}

	void adjust_direction() {
		this->dx = length * cos(angle * 3.1415 / 180.0);

		this->dy = length * sin(angle * 3.1415 / 180.0);

	}
};

struct Player {
	float speed, rotation_speed; 
	float vx = 0, vy = 0; 
	float x, y, r; 
	float delta_angle = 0, angle = 0; 
	int move_direction = 0; // 0 -> stationary; 1 -> forward; 2 -> backwards; 3 -> Left; 4 -> Right

	bool is_controlled_by_keyboard = false; 

	std::array<Ray, num_rays> rays; 

	sf::CircleShape shape; 

	Player(int x, int y, int r, float speed = 0.05, float rotation_speed = 0.05) : x(x), y(y), r(r), speed(speed), rotation_speed(rotation_speed){
		
		shape =  sf::CircleShape(r, 10); 
		
		shape.setFillColor(sf::Color::Blue); 

		shape.setOrigin(r, r); 

		shape.setPosition(x, y); 

		init_rays(); 

	}

	void calculate_movement() {

		float angle_in_rads = (angle + player_view_range / 2.f) / 180.0 * 3.1415; 

		switch (move_direction) {
			case 0: 
				vx = 0;
				vy = 0; 
				break; 
			case 1: // Forward
				vy = sin(angle_in_rads) * speed;
				vx = cos(angle_in_rads) * speed;
				break; 
			case 2: // Backwards
				vy = -sin(angle_in_rads) * speed;
				vx = -cos(angle_in_rads) * speed;
				break; 
			case 3: // Left
				vy = sin(angle_in_rads - 3.1415 / 2.f) * speed;
				vx = cos(angle_in_rads - 3.1415 / 2.f) * speed;
				break; 
			case 4: // Right
				vy = sin(angle_in_rads + 3.1415 / 2.f) * speed;
				vx = cos(angle_in_rads + 3.1415 / 2.f) * speed;
				break; 
		}

	}

	void toggel_control_mode() {
		is_controlled_by_keyboard = !is_controlled_by_keyboard; 
		vx = 0; 
		vy = 0; 
	}

	void init_rays() {
		for (int i = 0; i < num_rays; i++) {
			rays[i] = Ray(x, y, angle + angle_between_rays * i, 1000);
		}

	}

	void update_ray_position() {

		for (Ray& r : rays) {
			r.x = x;
			r.y = y;
		}

	}

	void update_ray_angle() {

		for (int i = 0; i < num_rays; i++) {
			rays[i].angle = this->angle + angle_between_rays * i; 
			rays[i].adjust_direction(); 
		}

		calculate_movement(); 

	}

	void advance_position(float delta) {
		x += vx * delta; 
		y += vy * delta;

		angle += delta_angle * delta; 

		update_position(); 

		update_ray_angle();

		update_ray_position(); 
	}

	void update_position() {
		shape.setPosition(x, y); 
	}
};


struct Obstacle {

	int x, y; 
	int w, h;

	bool is_rect; // 1 -> Rect; 0 -> Line

	bool is_in_creation; 

	Obstacle(int x, int y, int w, int h,bool is_rect = true, bool is_in_creation = true):
		x(x), y(y), w(w), h(h), is_rect(is_rect), is_in_creation(is_in_creation) {}
	
};

struct Line {
	int x, y, w, h; 
	int thickness; 
	float length, angle; 

	Line(int x, int y, int w, int h, int thickness, float angle = 0) : x(x), y(y), w(w), h(h), thickness(thickness), angle(angle) {

		this->length = sqrt((float)(w * w + h * h)); 

	}

	float calculate_angle() {

		return acos(w / length) * 180.0 / 3.1415; 

	}
};