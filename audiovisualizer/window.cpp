#include "window.hpp"
#include "Globals.hpp"
#include "FFT.hpp"
#include <thread>         // std::this_thread::sleep_for
#include <chrono>
#include <atomic>

window::window() : Window(sf::VideoMode(width, height), "Krilo - visual"){
	Window.setFramerateLimit(400);

	magnitudes.resize(N / 2 / 1.1);
	//magnitudes.resize(N / 2);

	//dot.setSize(sf::Vector2f(1, 1));
	dot.setRotation(270);
	dot.setFillColor(sf::Color::White);

	time.setCharacterSize(width / 64);
	time.setFillColor(sf::Color::White);
	time.setPosition(width / 16 * 15, height / 54);
	time.setFont(startMenu.font);

	widthOfDot = std::round(width / magnitudes.size()); // calculate width of dot based on number of stripes and width of window...
	//doesn't work properly

}

void window::windowRun()
{
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
		drawTime();

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
	}
	if (event.type == sf::Event::MouseWheelScrolled) {
		if (event.mouseWheelScroll.delta > 0 && fft.song.getVolume() < 100) fft.song.setVolume(fft.song.getVolume() + 10);
		else if(event.mouseWheelScroll.delta < 0 && fft.song.getVolume() > 0) fft.song.setVolume(fft.song.getVolume() - 10);
	}
}
void window::drawVisualization(std::vector<double> magnitudes){
	for (int i = 0; i < magnitudes.size(); i++) {
		dot.setSize(sf::Vector2f(magnitudes[i] / 10 / (magnitudes.size() - 0), 1)); /// (magnitudes.size() - i)
		dot.setPosition(sf::Vector2f(i * 1, height));
		Window.draw(dot);
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(23));
}

void window::drawTime() {
	timeString = std::to_string(fft.song.getPlayingOffset().asSeconds());
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

		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
			pressed = true;
			if (startMenu.clickBrowse(Window)) {
				startMenu.button = 1;
				startMenu.setPressed(startMenu.button);
			}
			else if (startMenu.clickStart(Window)) {
				startMenu.button = 2;
				startMenu.setPressed(startMenu.button);
			}
		}
		if (!startMenu.clickBrowse(Window) && startMenu.button == 1) {
			startMenu.setUnpressed(startMenu.button);
		}
		else if (!startMenu.clickStart(Window) && startMenu.button == 2) {
			startMenu.setUnpressed(startMenu.button);
		}
		if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left && pressed)
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
				pressed = false;
				break;
			}
		}
	}
}



