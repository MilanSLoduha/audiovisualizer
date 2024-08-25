#pragma once

#include "FFT.hpp"
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
	bool timeVisible = true;
	sf::RectangleShape dot;
	FFT fft;
	sf::Text time;
	std::string timeString;
	void drawTime();

	int widthOfDot = -1;
	bool needToRecalculateWidth = false;
	bool enderedWidth = false;
	int dotCount;
	int space;
	int shift;

	int visSide = 0;

	void buttonFunction(int& button);

	sf::Clock clock;
	StartMenu startMenu;
	sf::Image icon;

	sf::Texture backgroundTexture;
	sf::Sprite background;

	int xPos;
	int yPos;

	int maxFreq;
	int maxFreqIndex;

	int minFreq;
	int minFreqIndex;

	int xBegin; //beginning of the visualization
	int xEnd;
	int yBegin;
	int YofViz;
	/*int yEnd;*/

	int style;

	void setSizes();

	//void applyRes();
	void loadBackground();

	void runStartMenu();
	void startInput();
	void prepareStart();
	//std::vector<sf::Int16> samples;
	void recording();
	void musicPlaying();
};

//window::~window()
//{
//}