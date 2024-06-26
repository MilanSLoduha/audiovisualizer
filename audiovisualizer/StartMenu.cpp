#include "StartMenu.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>

StartMenu::StartMenu()
{
	isActive = true;
	
	//load textures and font from files, etc.
	{
		if (!backgroundTexture.loadFromFile(TexturePath + "background.png")) {
			std::cout << "Error loading background texture" << std::endl;
		}
		if (!buttonTexture.loadFromFile(TexturePath + "Button2.png")) {
			std::cout << "Error loading button texture" << std::endl;
		}
		if (!pressedButtonTexture.loadFromFile(TexturePath + "Button3.png")) {
			std::cout << "Error loading pressed button texture" << std::endl;
		}
		if (!leftResolutionTexture.loadFromFile(TexturePath + "left.png")) {
			std::cout << "Error loading leftResolution texture" << std::endl;
		}
		if (!rightResolutionTexture.loadFromFile(TexturePath + "right.png")) {
			std::cout << "Error loading rightResolution texture" << std::endl;
		}
		if (!pressedleftResolutionTexture.loadFromFile(TexturePath + "leftPressed.png")) {
			std::cout << "Error loading pressedleftResolution texture" << std::endl;
		}
		if (!pressedrightResolutionTexture.loadFromFile(TexturePath + "rightPressed.png")) {
			std::cout << "Error loading pressedrightResolution texture" << std::endl;
		}
		if (!ApplyButtonTexture.loadFromFile(TexturePath + "apply.png")) {
			std::cout << "Error loading ApplyButton texture" << std::endl;
		}
		if (!pressedApplyButtonTexture.loadFromFile(TexturePath + "applyPressed.png")) {
			std::cout << "Error loading pressedApplyButton texture" << std::endl;
		}
		if (!yesFullTexture.loadFromFile(TexturePath + "yes.png")) {
			std::cout << "Error loading yesFull texture" << std::endl;
		}
		if (!noFullTexture.loadFromFile(TexturePath + "no.png")) {
			std::cout << "Error loading noFull texture" << std::endl;
		}
		if (!paletteImage.loadFromFile(TexturePath + "palette1.png")) {
			std::cout << "Error loading palette texture" << std::endl;
		}
		if (!paletteTexture.loadFromImage(paletteImage)) {
			std::cout << "Error loading palette texture" << std::endl;
		}

		if (!font.loadFromFile("font.ttf")) {
			std::cout << "Error loading font" << std::endl;
		}
	}

	//set textures for sprites
	{
		Browse.textures.x = &pressedButtonTexture;
		Browse.textures.y = &buttonTexture;

		DecRes.textures.x = &pressedleftResolutionTexture;
		DecRes.textures.x = &leftResolutionTexture;

		IncRes.textures.x = &pressedrightResolutionTexture;
		IncRes.textures.x = &rightResolutionTexture;

		ApplyRes.textures.x = &pressedApplyButtonTexture;
		ApplyRes.textures.y = &ApplyButtonTexture;

		Fullscreen.textures.x = &yesFullTexture;
		Fullscreen.textures.y = &noFullTexture;

		PickColor.textures.x = &pressedApplyButtonTexture;
		PickColor.textures.y = &ApplyButtonTexture;

		ApplyColor.textures.x = &pressedApplyButtonTexture;
		ApplyColor.textures.y = &ApplyButtonTexture;

		background.setTexture(backgroundTexture);
		Start.setTexture(buttonTexture);
	}

	browseText.setFillColor(sf::Color::White);
	browseText.setFont(font);
	browseText.setString("Browse");

	startText.setFillColor(sf::Color::White);
	startText.setFont(font);
	startText.setString("Start");

	resolutionText.setFillColor(sf::Color::Cyan);
	resolutionText.setOutlineColor(sf::Color::Black);
	resolutionText.setOutlineThickness(2);
	resolutionText.setFont(font);
	resolutionText.setString(std::to_string(width[curRes]) + "x" + std::to_string(height[curRes]));

	setSizes();
}

void StartMenu::resizePalette()
{
	palette.setPosition(width[curRes] / 10 * 8, height[curRes] / 10 * 4);
	palette.setScale(width[curRes] / 1920. * 1.26, width[curRes] / 1920. * 1.26);

	color.setPosition(width[curRes] / 10 * 9.55, height[curRes] / 10 * 4.03);
	color.setSize(sf::Vector2f(width[curRes] / 23, width[curRes] / 23));
}

void StartMenu::getColors(const sf::RenderWindow& window)
{
	sf::Vector2f localPos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)) - palette.getPosition();
	if (localPos.x >= 0 && localPos.y >= 0 && localPos.x < palette.getGlobalBounds().width && localPos.y < palette.getGlobalBounds().height) {
		localPos.x /= palette.getScale().x; // Adjust for scaling
		localPos.y /= palette.getScale().y; // Adjust for scaling

		sf::Color pickedColor = paletteImage.getPixel(localPos.x, localPos.y);
		color.setFillColor(pickedColor);
	}
}

void StartMenu::setSizes()
{
	Browse.setPosition(width[curRes] * .8f, height[curRes] * .2f);
	Browse.setScale(width[curRes] / 48000.f, width[curRes] / 48000.f);

	Start.setPosition(width[curRes] * .8f, height[curRes] * .8f);
	Start.setScale(width[curRes] / 48000.f, width[curRes] / 48000.f);

	browseText.setCharacterSize(width[curRes] / 64.f);
	browseText.setPosition(width[curRes] * .8f, height[curRes] * .2f);

	startText.setCharacterSize(width[curRes] / 64.f);
	startText.setPosition(width[curRes] * .8f, height[curRes] * .8f);

	DecRes.setPosition(width[curRes] * .76f, height[curRes] * .3f);
	DecRes.setScale(width[curRes] / 4800.f, width[curRes] / 4800.f);

	IncRes.setPosition(width[curRes] * .92f, height[curRes] * .3f);
	IncRes.setScale(width[curRes] / 4800.f, width[curRes] / 4800.f);

	ApplyRes.setPosition(width[curRes] * .64f, height[curRes] * .3f);
	ApplyRes.setScale(width[curRes] / 4800.f, width[curRes] / 4800.f);

	background.setScale(width[curRes] / float(backgroundTexture.getSize().x), width[curRes] / float(backgroundTexture.getSize().y));

	resolutionText.setCharacterSize(width[curRes] / 64.f);
	resolutionText.setPosition(width[curRes] * .82f, height[curRes] * .33f);

	Fullscreen.setPosition(width[curRes] * .7f, height[curRes] * .3f);
	Fullscreen.setScale(width[curRes] / 4800.f, width[curRes] / 4800.f);

	PickColor.setPosition(width[curRes] * .7f, height[curRes] * .42f);
	PickColor.setScale(width[curRes] / 4800.f, width[curRes] / 4800.f);

	ApplyColor.setPosition(width[curRes] * .64f, height[curRes] * .6f);
	ApplyColor.setScale(width[curRes] / 4800.f, width[curRes] / 4800.f);
}


void StartMenu::draw(sf::RenderWindow& window)
{
	window.draw(background);
	window.draw(Browse);
	window.draw(Start);
	window.draw(browseText);
	window.draw(startText);
	window.draw(DecRes);
	window.draw(IncRes);
	window.draw(ApplyRes);
	window.draw(resolutionText);
	window.draw(Fullscreen);
	window.draw(PickColor);
	window.draw(ApplyColor);
	window.draw(palette);
	window.draw(color);
}

void StartMenu::changeResolution(int diff)
{
	if (diff == 1) {
		wantedRes++;
		if (wantedRes >= width.size()) wantedRes = 0;
	}
	else if (diff == -1) {
		wantedRes--;
		if (wantedRes < 0) wantedRes = width.size() - 1;
	}
	resolutionText.setString(std::to_string(width[wantedRes]) + "x" + std::to_string(height[wantedRes]));

}

void Button::setPressed() {
	setTexture(*textures.x);
}

void Button::setUnpressed() {
	setTexture(*textures.y);
}

bool Button::isClicked(sf::RenderWindow& window)
{
	return getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
}