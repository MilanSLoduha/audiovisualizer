#pragma once

#include "FFT.hpp"
#include <SFML/Graphics.hpp>
#include "Globals.hpp"
#include "StartMenu.hpp"

class window {
public:
	window();
	void windowRun();
	void handleInput(sf::Event& event, sf::RenderWindow& window, FFT& fft);
	sf::Event event;
	void drawVisualization(std::vector<double>);
	std::vector<double> magnitudes;
	//~window();
private:
	sf::RenderWindow Window;
	sf::RectangleShape dot;
	FFT fft;
	sf::Text time;
	sf::Font font;
	std::string timeString;
	void drawTime();
	int widthOfDot;
	sf::Clock clock;
	StartMenu startMenu;

	void startInput();
	//std::vector<sf::Int16> samples;
};

//window::~window()
//{
//}