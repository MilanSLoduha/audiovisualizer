#include "window.hpp"
#include "Globals.hpp"
#include "FFT.hpp"
#include <thread>         // std::this_thread::sleep_for
#include <chrono>

window::window() : Window(sf::VideoMode(width, height), "Krilo - visual"){
	// Optionally, set framerate limit or other window properties here
	Window.setFramerateLimit(60);
	magnitudes.resize(N / 2);

	//dot.setSize(sf::Vector2f(1, 1));
	dot.setRotation(270);
	dot.setFillColor(sf::Color::White);
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
		dot.setSize(sf::Vector2f(magnitudes[i] / 100, 1));
		dot.setPosition(sf::Vector2f(i, height));
		Window.draw(dot);
	}
	/*for (int i = 0; i < magnitudes.size(); i++) {
		dot.setSize(sf::Vector2f(1, magnitudes[i]));
		dot.setPosition(sf::Vector2f(i, magnitudes[i]));
		Window.draw(dot);
	}*/

	//for (int i = 0; i < 2000; i++) {

	//	//dot.setSize(sf::Vector2f(magnitudes[i], 20));
	//	////std::cout << magnitudes[i] << std::endl;
	//	//dot.setPosition(sf::Vector2f(i, height));
	//	////std::this_thread::sleep_for(std::chrono::milliseconds(1));
	//	//Window.draw(dot);
	//	//Window.display();
	//}
}
//window::~window()


