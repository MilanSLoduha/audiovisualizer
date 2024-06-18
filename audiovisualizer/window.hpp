#pragma once

#include "FFT.hpp"
#include <SFML/Graphics.hpp>
#include "Globals.hpp"

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
	int widthOfDot = std::round(width / fft.numberOfStripes); // calculate width of dot based on number of stripes and width of window...
															 //doesn't work properly
	//std::vector<sf::Int16> samples;
};

//window::~window()
//{
//}