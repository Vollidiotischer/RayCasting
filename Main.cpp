#include <iostream>

#include <thread>
#include <array>
#include <vector>


#include "Variables.h"
#include "MainLoop.h"
#include "RendererMain.h"


/*

Controls: 
	Player:
		[Space]: Toggle between Mouse and keyboard controlls
			Mouse Control:		Use the mouse to control the player (Default) 
			Keyboard Control:	Use [Up/Down/Right/Left] to control the player (from first person perspective) 
								Use [D/F] to rotate the player

	Objects
		[Mouse_Left (Drag)]: Create Square 
		[Mouse_Right (Drag)]: Crerate Line
*/


int main() {

	// Create Player Object and Obstacles List
	Player player(screen_width / 2, screen_height / 2, 15, 0.15, 0.2);
	std::vector<Obstacle> obstacles;


	// pass player and objects to both run functions by refference 
	std::thread t1(MainLoop::run, std::ref(player), std::ref(obstacles));

	RendererMain::run(player, obstacles); 

	// wait for the MainLoop::run function to finish
	t1.join(); 

	return 0; 
}