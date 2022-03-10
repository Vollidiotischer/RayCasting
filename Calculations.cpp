#include "Variables.h"

namespace Calculations {

	namespace {
		void update_player(Player& player) {

			player.x += player.vx; 
			player.y += player.vy; 

			player.update_position(); 
		}
	}

	void calculate_frame(Player& player) {

		update_player(player); 

	}

}