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
	dot.setOutlineColor(sf::Color::Cyan);
	//dot.setOutlineThickness(1);	

	time.setFillColor(sf::Color::White);
	time.setFont(startMenu.font);

	style = sf::Style::Default;

	//if (icon.loadFromFile(startMenu.TexturePath + "icon.png")) Window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}

void window::loadBackground()
{
	backgroundTexture.loadFromFile(startMenu.BackgroundPath);
	background.setTexture(backgroundTexture);
}

void window::runStartMenu() {
	while (Window.isOpen() && startMenu.startMenu) {
		startInput();

		Window.clear();
		startMenu.draw(Window);
		Window.display();
	}
}

void window::windowRun()
{
	setSizes();
	runStartMenu();

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
		Window.draw(background);
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
		if (event.key.code == sf::Keyboard::Escape) {
			startMenu.startMenu = true;
			runStartMenu();
		}
		if (event.key.code == sf::Keyboard::Right) fft.song.setPlayingOffset(fft.song.getPlayingOffset() + sf::seconds(10));
		if (event.key.code == sf::Keyboard::Left) fft.song.setPlayingOffset(fft.song.getPlayingOffset() - sf::seconds(10));
		if (event.key.code == sf::Keyboard::T) timeVisible = !timeVisible;
		if (event.key.code == sf::Keyboard::Up) std::cout << window.getSize().x << "  " << window.getSize().y << std::endl;
	}
	if (event.type == sf::Event::MouseWheelScrolled) {
		if (event.mouseWheelScroll.delta > 0 && fft.song.getVolume() < 100) fft.song.setVolume(fft.song.getVolume() + 10);
		else if(event.mouseWheelScroll.delta < 0 && fft.song.getVolume() > 0) fft.song.setVolume(fft.song.getVolume() - 10);
	}

	if (event.type == sf::Event::Resized) {
		startMenu.actualWidth = event.size.width;
		startMenu.actualHeight = event.size.height;
		Window.create(sf::VideoMode(startMenu.actualWidth, startMenu.actualHeight), "Krilo - visual", style);
		//Window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
		startMenu.setSizes();
		setSizes();
		startMenu.resizePalette();
	}
}
void window::drawVisualization(std::vector<double> magnitudes){
	for (int i = 0; i < magnitudes.size(); i++) {
		dot.setSize(sf::Vector2f(magnitudes[i] / 10 / (magnitudes.size() - 0), 1)); /// (magnitudes.size() - i)
		dot.setPosition(sf::Vector2f(i * 3, startMenu.actualHeight));
		Window.draw(dot);
	}
	//std::this_thread::sleep_for(std::chrono::milliseconds(23));
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
		case sf::Event::Resized: {
			startMenu.actualWidth = event.size.width;
			startMenu.actualHeight = event.size.height;
			xPos = Window.getPosition().x;
			yPos = Window.getPosition().y;
			Window.create(sf::VideoMode(startMenu.actualWidth, startMenu.actualHeight), "Krilo - visual", style);
			Window.setPosition(sf::Vector2i(xPos, yPos));
			Window.setFramerateLimit(60);
			startMenu.setSizes();
			setSizes();
			startMenu.resizePalette();
			break;
		}
		case sf::Event::KeyPressed: {
			if (startMenu.formMinSelected || startMenu.formMaxSelected) {
				if (event.key.code >= sf::Keyboard::Num0 && event.key.code <= sf::Keyboard::Num9) {
					if (startMenu.formMinSelected) {
						if (startMenu.formMinString == "Default") {
							startMenu.formMinString = "";
						}
						startMenu.formMinString += char(event.key.code + 22);
						startMenu.formMinText.setString(startMenu.formMinString);
					}
					else {
						if (startMenu.formMaxString == "Default") {
							startMenu.formMaxString = "";
						}
						startMenu.formMaxString += char(event.key.code + 22);
						startMenu.formMaxText.setString(startMenu.formMaxString);
					}
				}
				else if (event.key.code >= sf::Keyboard::Numpad0 && event.key.code <= sf::Keyboard::Numpad9) {
					if (startMenu.formMinSelected) {
						if (startMenu.formMinString == "Default") {
							startMenu.formMinString = "";
						}
						startMenu.formMinString += char(event.key.code - 27);
						startMenu.formMinText.setString(startMenu.formMinString);
					}
					else {
						if (startMenu.formMaxString == "Default") {
							startMenu.formMaxString = "";
						}
						startMenu.formMaxString += char(event.key.code - 27);
						startMenu.formMaxText.setString(startMenu.formMaxString);
					}
				}
				else if (event.key.code == sf::Keyboard::Backspace) {
					if (startMenu.formMinSelected) {
						if (!startMenu.formMinString.empty() && startMenu.formMinString != "Default") {
							startMenu.formMinString.pop_back();
							if (!startMenu.formMinString.empty()) {
								startMenu.formMinText.setString(startMenu.formMinString);
							}
							else {
								startMenu.formMinString = "Default";
								startMenu.formMinText.setString("Default");
							}
						}
					}
					else {
						if (!startMenu.formMaxString.empty() && startMenu.formMaxString != "Default") {
							startMenu.formMaxString.pop_back();
							if (!startMenu.formMaxString.empty()) {
								startMenu.formMaxText.setString(startMenu.formMaxString);
							}
							else {
								startMenu.formMaxText.setString("Default");
								startMenu.formMaxString = "Default";
								startMenu.formMinText.setString("Default");
								startMenu.formMinString = "Default";
							}
						}
					}
				}
			}

				if (startMenu.formMaxString != "Default" && stoi(startMenu.formMaxString) > 22000) {
					startMenu.formMaxString = "22000";
					startMenu.formMaxText.setString(startMenu.formMaxString);
				}
				if (startMenu.formMaxString != "Default" && startMenu.formMinString != "Default") {
					if (std::stoi(startMenu.formMinString) > std::stoi(startMenu.formMaxString)) {
						startMenu.formMinString = startMenu.formMaxText.getString();
						startMenu.formMinText.setString(startMenu.formMinString);
					}
				}

				if (startMenu.formMaxString == "Default" && startMenu.formMinString != "Default") {
					if (std::stoi(startMenu.formMinString) > 18000) {
						startMenu.formMinString = "18000";
						startMenu.formMinText.setString(startMenu.formMinString);
					}
				}
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
									  else if (startMenu.clikedFormMin(Window)) {
										  startMenu.formMinSelected = true;
										  startMenu.formMaxSelected = false;
										  break;
									  }
									  else if (startMenu.clikedFormMax(Window)) {
										  startMenu.formMaxSelected = true;
										  startMenu.formMinSelected = false;
										  break;
									  }
									  startMenu.formMinSelected = false;
									  startMenu.formMaxSelected = false;
								  }
								  if (!startMenu.clickBrowse(Window) && startMenu.button == 1) { //if mouse is not on button but mouse button is pressed
									  startMenu.setUnpressed(startMenu.button);
									  startMenu.button = 0;
								  }
								  else if (!startMenu.clickStart(Window) && startMenu.button == 2) {
									  startMenu.setUnpressed(startMenu.button);
									  startMenu.button = 0;
								  }
								  else if (!startMenu.clickLeftResolution(Window) && startMenu.button == 3) {
									  startMenu.setUnpressed(startMenu.button);
									  startMenu.button = 0;
								  }
								  else if (!startMenu.clickRightResolution(Window) && startMenu.button == 4) {
									  startMenu.setUnpressed(startMenu.button);
									  startMenu.button = 0;
								  }
								  else if (!startMenu.clickApply(Window) && startMenu.button == 5) {
									  startMenu.setUnpressed(startMenu.button);
									  startMenu.button = 0;
								  }
								  else if (!startMenu.clickChooseColor(Window) && startMenu.button == 7) {
									  startMenu.setUnpressed(startMenu.button);
									  startMenu.button = 0;
								  }
								  else if (!startMenu.clickApplyColor(Window) && startMenu.button == 8) {
									  startMenu.setUnpressed(startMenu.button);
									  startMenu.button = 0;
								  }

								  if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left && pressed) //if mouse button is released
								  {
									  if (startMenu.clickBrowse(Window)) {
										  startMenu.button = 1;
										  startMenu.setUnpressed(startMenu.button);
										  pressed = false;
										  Window.setVisible(false);
										  startMenu.browseFile();
										  Window.setVisible(true);
									  }

									  else if (startMenu.clickStart(Window)) {
										  startMenu.button = 2;
										  startMenu.setUnpressed(startMenu.button);
										  startMenu.startMenu = false;
										  prepareStart();
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
void window::prepareStart() {
	fft.loadMusic(startMenu.MusicPath);
	setSizes();
	if (startMenu.color.getFillColor() != sf::Color::White) dot.setFillColor(startMenu.color.getFillColor());
	if (!startMenu.BackgroundPath.empty()) {
		loadBackground();
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
		Window.create(sf::VideoMode(width[startMenu.wantedRes], height[startMenu.wantedRes]), "Krilo - visual", sf::Style::Default);

		style = sf::Style::Default;
		startMenu.setFullScreen = false;
	}
	else {
		Window.create(sf::VideoMode(width[startMenu.wantedRes], height[startMenu.wantedRes]), "Krilo - visual", style);
	}
	startMenu.actualHeight = height[startMenu.wantedRes];
	startMenu.actualWidth = width[startMenu.wantedRes];
	Window.setFramerateLimit(60);
	//Window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	startMenu.curRes = startMenu.wantedRes;
	startMenu.setSizes();
	setSizes();
	startMenu.resizePalette();
}

void window::setSizes()
{
	time.setCharacterSize(startMenu.actualWidth / 64);
	widthOfDot = std::round(startMenu.actualWidth / magnitudes.size());
	time.setPosition(startMenu.actualWidth / 16 * 13.5, startMenu.actualHeight / 54); // (width[startMenu.curRes] / 16 * 15, height[startMenu.curRes] / 54)
}



