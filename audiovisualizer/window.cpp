#include "window.hpp"
#include "Globals.hpp"

window::window() : Window(sf::VideoMode(width, height), "Krilo - visual") {
	// Optionally, set framerate limit or other window properties here
	Window.setFramerateLimit(60);
}

void window::windowRun()
{
	while (Window.isOpen())
	{
		while (Window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				Window.close();
		}

		Window.clear();
		Window.display();
	}
}
//window::~window()


