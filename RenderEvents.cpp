
#include <SFML/Graphics.hpp>	

namespace RenderEvents {

	void event_handler(sf::RenderWindow& rw) {

		sf::Event events;
		while (rw.pollEvent(events)) {
			if (events.type == sf::Event::Closed) {
				rw.close();
			}
		}
	}

}