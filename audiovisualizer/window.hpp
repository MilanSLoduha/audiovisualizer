#pragma once

#include "FFT.hpp"
#include <SFML/Graphics.hpp>
#include "Globals.hpp"

class window {
public:
	window();
	void windowRun();
	sf::RenderWindow Window;
	void handleInput(sf::Event& event, sf::RenderWindow& window, FFT& fft);
	FFT fft;
	sf::Event event;
	//~window();
};

//window::~window()
//{
//}