
//#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"
//#define SCREEN_WIDTH 1024
//#define SCREEN_HEIGHT 1024

#include "DEFINITIONS.h"

int main()
{
	NWP::Game(SCREEN_WIDTH, SCREEN_HEIGHT, "tick-tac-toe");

	return EXIT_SUCCESS;
	/*sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Game");

	while (window.isOpen()) {
		sf::Event event;

		while (window.pollEvent(event)) {
			switch (event.type) {
				case sf::Event::Closed:
					window.close();
					break;
			}
		}

		window.clear();

		window.display();
	}*/
}
