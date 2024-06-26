#include "window.hpp"
#include "Globals.hpp"
#include "FFT.hpp"
#include <thread>         // std::this_thread::sleep_for
#include <chrono>
#include <atomic>

window::window() : Window(sf::VideoMode(width[startMenu.curRes], height[startMenu.curRes]), "Krilo - visual") {
	Window.setFramerateLimit(60);

	magnitudes.resize(N / 2 / 1.1);
	//magnitudes.resize(N / 2);

	//dot.setSize(sf::Vector2f(1, 1));
	dot.setRotation(270);
	dot.setFillColor(sf::Color::White);

	time.setFillColor(sf::Color::White);
	time.setFont(startMenu.font);
}

void window::windowRun()
{
	setSizes();
	while (Window.isOpen() && startMenu.startMenu) {
		startInput();

		Window.clear();
		startMenu.draw(Window);
		Window.display();
	}

    fft.song.play();
    while (Window.isOpen())
    {
        while (Window.pollEvent(event))
        {
            handleInput(event, Window, fft);
        }
		if (clock.getElapsedTime().asMilliseconds() > 23)
		{
			fft.applyFFT(fft.samples_fft, magnitudes);
			clock.restart();
		}

        Window.clear();
		drawVisualization(magnitudes);
		if (timeVisible) drawTime();

        Window.display();
    }
}

void window::handleInput(sf::Event& event, sf::RenderWindow& window, FFT& fft) {
	if (event.type == sf::Event::Closed) {
		window.close();
	}
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Space)
		{	
			if (fft.song.getStatus() == sf::Sound::Status::Paused) fft.song.play();
			else if(fft.song.getStatus() == sf::Sound::Status::Playing) fft.song.pause();
		}
		if (event.key.code == sf::Keyboard::Escape) window.close();
		if (event.key.code == sf::Keyboard::Right) fft.song.setPlayingOffset(fft.song.getPlayingOffset() + sf::seconds(10));
		if (event.key.code == sf::Keyboard::Left) fft.song.setPlayingOffset(fft.song.getPlayingOffset() - sf::seconds(10));
		if (event.key.code == sf::Keyboard::T) timeVisible = !timeVisible;
	}
	if (event.type == sf::Event::MouseWheelScrolled) {
		if (event.mouseWheelScroll.delta > 0 && fft.song.getVolume() < 100) fft.song.setVolume(fft.song.getVolume() + 10);
		else if(event.mouseWheelScroll.delta < 0 && fft.song.getVolume() > 0) fft.song.setVolume(fft.song.getVolume() - 10);
	}
}
void window::drawVisualization(std::vector<double> magnitudes){
	for (int i = 0; i < magnitudes.size(); i++) {
		dot.setSize(sf::Vector2f(magnitudes[i] / 10 / (magnitudes.size() - 0), 1)); /// (magnitudes.size() - i)
		dot.setPosition(sf::Vector2f(i * 1, height[startMenu.curRes]));
		Window.draw(dot);
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(23));
}

void window::drawTime() {
	timeString = std::to_string(fft.song.getPlayingOffset().asSeconds());
	timeString.erase(timeString.length() - 4);
	timeString += " / " + std::to_string(fft.music.getDuration().asSeconds());
	timeString.erase(timeString.length() - 4);
	time.setString(timeString);
	Window.draw(time);
}
//window::~window()

void window::startInput()
{
	bool pressed = true;

	while (Window.pollEvent(event)) {
		switch (event.type) {

		case sf::Event::Closed: {
			Window.close();

			break;
		}
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			sf::Vector2i mousePos = sf::Mouse::getPosition(Window);

			if (startMenu.palette.getGlobalBounds().contains(Window.mapPixelToCoords(mousePos))) {
				startMenu.getColors(Window);
			}
		}
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) { //if button is pressed
			pressed = true;
			if (startMenu.clickBrowse(Window)) {
				startMenu.button = 1;
				startMenu.setPressed(startMenu.button);
			}
			else if (startMenu.clickStart(Window)) {
				startMenu.button = 2;
				startMenu.setPressed(startMenu.button);
			}
			else if (startMenu.clickLeftResolution(Window)) {
				startMenu.button = 3;
				startMenu.setPressed(startMenu.button);
			}
			else if (startMenu.clickRightResolution(Window)) {
				startMenu.button = 4;
				startMenu.setPressed(startMenu.button);
			}
			else if (startMenu.clickApply(Window)) {
				startMenu.button = 5;
				startMenu.setPressed(startMenu.button);
			}
			else if (startMenu.clickChooseColor(Window)) {
				startMenu.button = 7;
				startMenu.setPressed(startMenu.button);
			}
			else if (startMenu.clickApplyColor(Window)) {
				startMenu.button = 8;
				startMenu.setPressed(startMenu.button);
			}
		}
		if (!startMenu.clickBrowse(Window) && startMenu.button == 1) { //if mouse is not on button but mouse button is pressed
			startMenu.setUnpressed(startMenu.button);
		}
		else if (!startMenu.clickStart(Window) && startMenu.button == 2) {
			startMenu.setUnpressed(startMenu.button);
		}
		else if (!startMenu.clickLeftResolution(Window) && startMenu.button == 3) {
			startMenu.setUnpressed(startMenu.button);
		}
		else if (!startMenu.clickRightResolution(Window) && startMenu.button == 4) {
			startMenu.setUnpressed(startMenu.button);
		}
		else if (!startMenu.clickApply(Window) && startMenu.button == 5) {
			startMenu.setUnpressed(startMenu.button);
		}
		else if (!startMenu.clickChooseColor(Window) && startMenu.button == 7) {
			startMenu.setUnpressed(startMenu.button);
		}
		else if (!startMenu.clickApplyColor(Window) && startMenu.button == 8) {
			startMenu.setUnpressed(startMenu.button);
		}

		if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left && pressed) //if mouse button is released
		{
			if (startMenu.clickBrowse(Window)) {
				startMenu.button = 1;
				startMenu.setUnpressed(startMenu.button);
				pressed = false;
			}

			else if (startMenu.clickStart(Window)) {
				startMenu.button = 2;
				startMenu.setUnpressed(startMenu.button);
				startMenu.startMenu = false;
				dot.setFillColor(startMenu.color.getFillColor());
				pressed = false;
			}
			else if (startMenu.clickLeftResolution(Window)) { //if left resolution button is clicked
				startMenu.button = 3;
				startMenu.setUnpressed(startMenu.button);
				pressed = false;
				startMenu.changeResolution(-1);
			}
			else if (startMenu.clickRightResolution(Window)) { //if right resolution button is clicked
				startMenu.button = 4;
				startMenu.setUnpressed(startMenu.button);
				pressed = false;
				startMenu.changeResolution(1);
			}
			else if (startMenu.clickApply(Window)) { //if apply button is clicked
				startMenu.button = 5;
				startMenu.setUnpressed(startMenu.button);
				pressed = false;
				applyRes();
			}
			else if (startMenu.clickYesFull(Window)) { //if fullscreen button is clicked
				startMenu.button = 6;
				if (startMenu.fullScreen) startMenu.setUnpressed(startMenu.button);
				else startMenu.setPressed(startMenu.button);
				startMenu.fullScreen = !startMenu.fullScreen;
			}
			else if (startMenu.clickChooseColor(Window)) { //if choose color button is clicked
				startMenu.button = 7;
				startMenu.setUnpressed(startMenu.button);
				pressed = false;
			}
			else if (startMenu.clickApplyColor(Window)) { //if apply color button is clicked
				startMenu.button = 8;
				startMenu.setUnpressed(startMenu.button);
				pressed = false;
			}
		}
	}
}

void window::applyRes()
{
	if (startMenu.fullScreen && !startMenu.setFullScreen) {
		Window.create(sf::VideoMode(width[startMenu.wantedRes], height[startMenu.wantedRes]), "Krilo - visual", sf::Style::None);

		style = sf::Style::None;
		startMenu.setFullScreen = true;
	}
	else if (!startMenu.fullScreen && startMenu.setFullScreen) {
		Window.create(sf::VideoMode(width[startMenu.wantedRes], height[startMenu.wantedRes]), "Krilo - visual", sf::Style::Close);

		style = sf::Style::Close;
		startMenu.setFullScreen = false;
	}
	else {
		Window.create(sf::VideoMode(width[startMenu.wantedRes], height[startMenu.wantedRes]), "Krilo - visual", style);
	}
	startMenu.curRes = startMenu.wantedRes;
	startMenu.setSizes();
	setSizes();
	startMenu.resizePalette();
}

void window::setSizes()
{
	time.setCharacterSize(width[startMenu.curRes] / 64);
	widthOfDot = std::round(width[startMenu.curRes] / magnitudes.size());
	time.setPosition(width[startMenu.curRes] / 16 * 13.5, height[startMenu.curRes] / 54); // (width[startMenu.curRes] / 16 * 15, height[startMenu.curRes] / 54)
}



