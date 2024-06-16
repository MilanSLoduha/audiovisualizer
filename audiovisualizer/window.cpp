#include "window.hpp"
#include "Globals.hpp"
#include "FFT.hpp"

window::window() : Window(sf::VideoMode(width, height), "Krilo - visual") {
	// Optionally, set framerate limit or other window properties here
	Window.setFramerateLimit(60);
}

void window::windowRun()
{
    fft.song.play();
    while (Window.isOpen())
    {
        while (Window.pollEvent(event))
        {
            handleInput(event, Window, fft);
            //fft.applyFFT(fft.music.getSamples(), fft.magnitudes);
        }
        Window.clear();
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
//window::~window()


