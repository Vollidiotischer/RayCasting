#pragma once

#include <SFML/Graphics.hpp>


constexpr int screen_width = 750; 
constexpr int screen_height = 750;


struct Line {
	int x1, x2, y1, y2; 
	Line(int x1, int y1, int x2, int y2) :
		x1(x1), x2(x2), y1(y1), y2(y2) {}
};

struct Player {
	float vx = 0, vy = 0; 
	float x, y, r; 
	float angle = 0; 
	sf::CircleShape *shape; 
	Player(int x, int y, int r) : x(x), y(y), r(r) {
		
		shape = new sf::CircleShape((float)r); 
		
		shape->setPointCount(10); 

		shape->setFillColor(sf::Color::Blue); 

		shape->setPosition(x, y); 

	}

	void update_position() {
		this->shape->setPosition(x, y); 
	}
};


struct Obstacle {

	int x, y; 
	int w, h; 

	Obstacle(int x, int y, int w, int h):
		x(x), y(y), w(w), h(h) {}
	
};