#include "MainLoop.h"


/*

Controls: 
	Player:
		[Space]: Toggle between Mouse and keyboard controlls
			Mouse Control: Use the mouse to control the player (Default) 
			Keyboard Control: Use [Up/Down/Right/Left] to control the player

	Objects
		[Mouse_Left (Drag)]: Create Square 
		[Mouse_Right (Drag)]: Crerate Line
*/


int main() {

	MainLoop::run(); 

	return 0; 
}