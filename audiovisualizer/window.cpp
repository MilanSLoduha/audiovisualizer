#include "window.hpp"
#include <thread>         // std::this_thread::sleep_for
#include <chrono>
#include <atomic>

window::window() : Window(sf::VideoMode(width[startMenu.curRes], height[startMenu.curRes]), "Krilo - visual") {
	Window.setFramerateLimit(60);


	//dot.setSize(sf::Vector2f(1, 1));
	dot.setRotation(270); //270
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
			fft.song.pause();
			sf::Time old = fft.song.getPlayingOffset();
			std::string oldPath = startMenu.MusicPath;
			runStartMenu();
			if (oldPath == startMenu.MusicPath) {
				fft.song.setPlayingOffset(old);
			}
			fft.song.play();
		}
		if (event.key.code == sf::Keyboard::Right) fft.song.setPlayingOffset(fft.song.getPlayingOffset() + sf::seconds(10));
		if (event.key.code == sf::Keyboard::Left) fft.song.setPlayingOffset(fft.song.getPlayingOffset() - sf::seconds(10));
		if (event.key.code == sf::Keyboard::T) timeVisible = !timeVisible;
	}
	if (event.type == sf::Event::MouseWheelScrolled) {
		if (event.mouseWheelScroll.delta > 0 && fft.song.getVolume() < 100) fft.song.setVolume(fft.song.getVolume() + 10);
		else if(event.mouseWheelScroll.delta < 0 && fft.song.getVolume() > 0) fft.song.setVolume(fft.song.getVolume() - 10);
	}

	if (event.type == sf::Event::Resized) {
		startMenu.actualWidth = event.size.width;
		startMenu.actualHeight = event.size.height;
		xEnd = startMenu.actualWidth;
		Window.create(sf::VideoMode(startMenu.actualWidth, startMenu.actualHeight), "Krilo - visual", style);
		//Window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
		startMenu.setSizes();
		needToRecalculateWidth = true;
		setSizes();
		startMenu.resizePalette();
	}
}
void window::drawVisualization(std::vector<double> magnitudes){
	for (int i = minFreqIndex; i <= maxFreqIndex; i++) {
		/*if(i % 3 == 0) dot.setFillColor(sf::Color::Cyan);
		else dot.setFillColor(sf::Color::White);*/
		dot.setSize(sf::Vector2f(magnitudes[i], widthOfDot)); /// (magnitudes.size() - i) // / 10 / (magnitudes.size() - 0)
		dot.setPosition(sf::Vector2f((i - minFreqIndex) * shift + xBegin, YofViz));
		//dot.setPosition(sf::Vector2f(20,20));
		//dot.setSize(sf::Vector2f(20, 20));
		//dot.setPosition(sf::Vector2f((i - shift2) * shift, YofViz)); // (i - minFreqIndex + xBegin) * (widthOfDot + Space), YofViz
		Window.draw(dot);
		if (visSide == 1 || visSide == 2) {
			dot.setRotation(90);
			dot.setPosition(sf::Vector2f((i - minFreqIndex) * shift + xBegin + widthOfDot, startMenu.actualHeight - yBegin));
			Window.draw(dot);
			dot.setRotation(270);
		}
		if ((i - minFreqIndex) * shift + xBegin >= xEnd) {
			//std::cout << i << " " << shift2 << " " << shift << " " << xEnd << std::endl;
			break;
		}
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
			startMenu.resizePalette();
			break;
		}
		case sf::Event::KeyPressed: {
			if (startMenu.formSelected) { //startMenu.formYendSelected
				if (event.key.code >= sf::Keyboard::Num0 && event.key.code <= sf::Keyboard::Num9) {
					if (startMenu.formStrings[startMenu.wantedForm] == startMenu.defaultStrings[startMenu.wantedForm]) {
						if (startMenu.defaultStrings[startMenu.wantedForm] != "1") {
							startMenu.formStrings[startMenu.wantedForm] = "";
						}

						startMenu.formStrings[startMenu.wantedForm] += char(event.key.code + 22);
						startMenu.FormText.setString(startMenu.formStrings[startMenu.wantedForm]);
					}
					else if (startMenu.formStrings[startMenu.wantedForm].length() < 5) {
						if (startMenu.formStrings[startMenu.wantedForm] == "0") {
							startMenu.formStrings[startMenu.wantedForm] = "";
						}
						startMenu.formStrings[startMenu.wantedForm] += char(event.key.code + 22);
						startMenu.FormText.setString(startMenu.formStrings[startMenu.wantedForm]);
					}
				}
				else if (event.key.code >= sf::Keyboard::Numpad0 && event.key.code <= sf::Keyboard::Numpad9) {
					if (startMenu.formStrings[startMenu.wantedForm] == startMenu.defaultStrings[startMenu.wantedForm]) {
						if (startMenu.defaultStrings[startMenu.wantedForm] != "1") {
							startMenu.formStrings[startMenu.wantedForm] = "";
						}

						startMenu.formStrings[startMenu.wantedForm] += char(event.key.code - 27);
						startMenu.FormText.setString(startMenu.formStrings[startMenu.wantedForm]);
					}
					else if (startMenu.formStrings[startMenu.wantedForm].length() < 5) {
						if (startMenu.formStrings[startMenu.wantedForm] == "0") {
							startMenu.formStrings[startMenu.wantedForm] = "";
						}
						startMenu.formStrings[startMenu.wantedForm] += char(event.key.code - 27);
						startMenu.FormText.setString(startMenu.formStrings[startMenu.wantedForm]);
					}
				}

				else if (event.key.code == sf::Keyboard::Backspace) {
					if (startMenu.formSelected) {
						if (!startMenu.formStrings[startMenu.wantedForm].empty() && startMenu.formStrings[startMenu.wantedForm] != "0" && startMenu.formStrings[startMenu.wantedForm] != startMenu.defaultStrings[startMenu.wantedForm]) {
							startMenu.formStrings[startMenu.wantedForm].pop_back();
							if (!startMenu.formStrings[startMenu.wantedForm].empty()) {
								startMenu.FormText.setString(startMenu.formStrings[startMenu.wantedForm]);
							}
							else {
								startMenu.formStrings[startMenu.wantedForm] = startMenu.defaultStrings[startMenu.wantedForm];
								startMenu.FormText.setString(startMenu.formStrings[startMenu.wantedForm]);
							}
						}
						else if (startMenu.defaultStrings[startMenu.wantedForm] == "1" && startMenu.formStrings[startMenu.wantedForm] == "1") {
							startMenu.formStrings[startMenu.wantedForm] = "0";
							startMenu.FormText.setString(startMenu.formStrings[startMenu.wantedForm]);
						}
					}
				}
			}

		/*	if (startMenu.formMaxString != "Default" && stoi(startMenu.formMaxString) > 22000) {
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
			}*/


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
									  else if (startMenu.clikedForm(Window)) {
										  if (startMenu.wantedForm < 8) {
											startMenu.formSelected = true;
										  }
										  else {
											  buttonFunction(startMenu.wantedForm);
										  }
											break;
									  }
									  startMenu.formSelected = false;
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
										  startMenu.changeForm(-1);
									  }
									  else if (startMenu.clickRightResolution(Window)) { //if right resolution button is clicked
										  startMenu.button = 4;
										  startMenu.setUnpressed(startMenu.button);
										  pressed = false;
										  startMenu.changeForm(1);
									  }
									  else if (startMenu.clickYesFull(Window)) { //if fullscreen button is clicked
										  startMenu.button = 6;
										  if (startMenu.fullScreen) startMenu.setUnpressed(startMenu.button);
										  else startMenu.setPressed(startMenu.button);
										  startMenu.fullScreen = !startMenu.fullScreen;
									  }
								  }
		}
	

}

void window::prepareStart() {
	fft.loadMusic(startMenu.MusicPath);

	/*xBegin = std::stoi(startMenu.xbeginString);
	yBegin = std::stoi(startMenu.ybeginString);*/

	if (startMenu.color.getFillColor() != sf::Color::White) dot.setFillColor(startMenu.color.getFillColor());
	if (!startMenu.BackgroundPath.empty()) {
		loadBackground();
	}

	for (int i = 0; i < startMenu.formsSize; i++) {
		if (startMenu.formStrings[i] != startMenu.defaultStrings[i]) { //if they are entered
			if (i == startMenu.MinHz) minFreq = std::stoi(startMenu.formStrings[i]);
			else if (i == startMenu.MaxHz) maxFreq = std::stoi(startMenu.formStrings[i]);
			else if (i == startMenu.Xbegin) xBegin = std::stoi(startMenu.formStrings[i]);
			else if (i == startMenu.Y) yBegin = std::stoi(startMenu.formStrings[i]);
			else if (i == startMenu.Xend) xEnd = std::stoi(startMenu.formStrings[i]);
			else if (i == startMenu.MaxMag) fft.maxMag = std::stoi(startMenu.formStrings[i]);
			else if (i == startMenu.Space) space = std::stoi(startMenu.formStrings[i]);
			else if (i == startMenu.DotSize) { 
				widthOfDot = std::stoi(startMenu.formStrings[i]); 
				enderedWidth = true;
			}
			else if (i == startMenu.Smoothinglevel) {
				if (startMenu.FormText.getString() == "Off") fft.smoothing = 0;
				else if (startMenu.FormText.getString() == "Mid") fft.smoothing = 1;
				else if (startMenu.FormText.getString() == "High") fft.smoothing = 2;
			}
			else if (i == startMenu.Side) {
				if (startMenu.formStrings[9] == "A") visSide = 0;
				else if (startMenu.formStrings[9] == "B") visSide = 1;
				else if (startMenu.formStrings[9] == "AB") visSide = 2;
			}
			//else if (i == startMenu.Side) style = std::stoi(startMenu.formStrings[i]);
		}
		else {
			if (i == startMenu.MinHz) minFreq = 0; //if not
			else if (i == startMenu.MaxHz) maxFreq = 22000;
			else if (i == startMenu.Xbegin) xBegin = 0;
			else if (i == startMenu.Y) yBegin = 0;
			else if (i == startMenu.Xend) xEnd = startMenu.actualWidth;
			else if (i == startMenu.MaxMag) fft.maxMag = 32000;
			else if (i == startMenu.Space) space = 1;
			else if (i == startMenu.DotSize) {
				enderedWidth = false;
			}
			//else if (i == startMenu.Space)  = std::stoi(startMenu.formStrings[i]);
			else if (i == startMenu.Smoothinglevel) {
				if (startMenu.formStrings[8] == "Off") fft.smoothing = 0;
				else if (startMenu.formStrings[8] == "Mid") fft.smoothing = 1;
				else if (startMenu.formStrings[8] == "High") fft.smoothing = 2;
			}
			else if (i == startMenu.Side) {
				if (startMenu.formStrings[9] == "A") visSide = 0;
				else if (startMenu.formStrings[9] == "B") visSide = 1;
				else if (startMenu.formStrings[9] == "AB") visSide = 2;
			}
			//else if (i == startMenu.Side) style = std::stoi(startMenu.formStrings[i]);
		}
	}

	//if (startMenu.yendString != "Default") yEnd = std::stoi(startMenu.yendString);
	//else yEnd = startMenu.actualHeight;
	if (fft.smoothing == 2) {
		maxFreqIndex = static_cast<float>(maxFreq) * static_cast<float>(N) / static_cast<float>(fft.sampleRate) * static_cast<float>(fft.smoothingDots) - 2;
		minFreqIndex = minFreq * N / fft.sampleRate * fft.smoothingDots;
	}
	else {
		maxFreqIndex = maxFreq * N / fft.sampleRate;
		minFreqIndex = minFreq * N / fft.sampleRate;
	}
	needToRecalculateWidth = true;
	setSizes();
}

void window::setSizes()
{
	time.setCharacterSize(startMenu.actualWidth / 64);
	time.setPosition(startMenu.actualWidth / 16 * 13.5, startMenu.actualHeight / 54); // (width[startMenu.curRes] / 16 * 15, height[startMenu.curRes] / 54)
	YofViz = startMenu.actualHeight - yBegin;
	dotCount = maxFreqIndex - minFreqIndex;
	//std::cout << dotCount << std::endl;
	if ((widthOfDot == -1 || needToRecalculateWidth) && !enderedWidth) {
		widthOfDot = xEnd / dotCount; //ked si druhykrat zada sirku treba tam dat needToRecalculateWidth = true//edit netreba
		needToRecalculateWidth = false;
	}
	if (widthOfDot < 1) widthOfDot = 1;

	shift = widthOfDot + space;
}

void window::buttonFunction(int& button) {
	if (button == 8) {
		startMenu.selectedSmoothing++;
		startMenu.selectedSmoothing %= 3;
		startMenu.formStrings[button] = startMenu.smoothingStrings[startMenu.selectedSmoothing];
		startMenu.FormText.setString(startMenu.formStrings[button]);
		startMenu.Form.setTexture(startMenu.smoothingTextures[startMenu.selectedSmoothing]);
	}
	else if (button == 9) {
		startMenu.selectedSide++;
		startMenu.selectedSide %= 3;
		startMenu.formStrings[button] = startMenu.sideStrings[startMenu.selectedSide];
		startMenu.Form.setTexture(startMenu.sideTextures[startMenu.selectedSide]);
	}
}



