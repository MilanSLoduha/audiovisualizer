#include "window.hpp"
#include "Globals.hpp"
#include "FFT.hpp"
#include <thread>         // std::this_thread::sleep_for
#include <chrono>
#include <atomic>
#include <iomanip>

window::window() : Window(sf::VideoMode(width, height), "Krilo - visual"){
	// Optionally, set framerate limit or other window properties here
	Window.setFramerateLimit(60);
	magnitudes.resize(N / 2);
	if (!font.loadFromFile("font.ttf")) {
		std::cout << "Error loading font" << std::endl;
	}
	//dot.setSize(sf::Vector2f(1, 1));
	dot.setRotation(270);
	dot.setFillColor(sf::Color::White);

	time.setCharacterSize(width / 64);
	time.setFillColor(sf::Color::White);
	time.setPosition(width / 16 * 15, height / 54);
	time.setFont(font);

}

void window::windowRun()
{
    fft.song.play();
    while (Window.isOpen())
    {
        while (Window.pollEvent(event))
        {
            handleInput(event, Window, fft);
        }
        fft.applyFFT(fft.samples_fft, magnitudes);

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
	}
	if (event.type == sf::Event::MouseWheelScrolled) {
		if (event.mouseWheelScroll.delta > 0) fft.song.setVolume(fft.song.getVolume() + 10);
		else fft.song.setVolume(fft.song.getVolume() - 10);
	}
}
void window::drawVisualization(std::vector<double> magnitudes){
	for (int i = 0; i < magnitudes.size(); i++) {
		dot.setSize(sf::Vector2f(magnitudes[i] / 10 / (magnitudes.size() - i), 1));
		dot.setPosition(sf::Vector2f(i, height));
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


