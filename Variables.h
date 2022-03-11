#pragma once

#include <SFML/Graphics.hpp>


constexpr int screen_width = 750; 
constexpr int screen_height = 750;

constexpr float angle_between_rays = 2; // in degrees 
constexpr int num_rays = 360 / angle_between_rays; 


struct Line {
	int x1, x2, y1, y2; 

	Line(int x1, int y1, int x2, int y2) :
		x1(x1), x2(x2), y1(y1), y2(y2) {}
};

struct Ray {
	int x, y; 
	float length, angle; 
	float dx = 0, dy = 0; 

	Ray() : x(0), y(0), length(0), angle(0) {}

	Ray(int x, int y, float angle, float length = 0) : x(x), y(y), angle(angle), length(length) {
	
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
	float speed; 
	float vx = 0, vy = 0; 
	float x, y, r; 
	float angle = 0; 

	std::array<Ray, num_rays> rays; 

	sf::CircleShape shape; 

	Player(int x, int y, int r, float speed = 0.05) : x(x), y(y), r(r), speed(speed) {
		
		shape =  sf::CircleShape(r, 10); 
		
		shape.setFillColor(sf::Color::Blue); 

		shape.setOrigin(r, r); 

		shape.setPosition(x, y); 

		init_rays(); 

	}

	void init_rays() {
		for (int i = 0; i < num_rays; i++) {
			rays[i] = Ray(x, y, angle_between_rays * i, 1000);
		}

	}

	void update_ray_position() {

		for (Ray& r : rays) {
			r.x = x;
			r.y = y;
		}

	}

	void advance_position(float delta) {
		x += vx * delta; 
		y += vy * delta;

		update_position(); 
	}

	void update_position() {
		shape.setPosition(x, y); 
	}
};


struct Obstacle {

	int x, y; 
	int w, h; 

	bool is_in_creation; 

	Obstacle(int x, int y, int w, int h, bool is_in_creation = true):
		x(x), y(y), w(w), h(h), is_in_creation(is_in_creation) {}
	
};