#pragma once

#include <SFML/Graphics.hpp>
#include "Globals.hpp"

class window {
public:
	window();
	void windowRun();
	sf::RenderWindow Window;
	//~window();

private:
	sf::Event event;
};

//window::~window()
//{
//}