#pragma once

#include <SFML/Graphics.hpp>
#include <shobjidl.h>
#include <Windows.h>
#include "Globals.hpp"

class Button : public sf::Sprite
{
public:
	Button() {};
	bool isClicked(sf::RenderWindow&);

	void setPressed();
	void setUnpressed();

	sf::Vector2<sf::Texture*> textures; //x is for pressed, y is for unpressed
};

class StartMenu
{
public:
	StartMenu();
	void setSizes();

	bool isActive;
	int curRes = 0;
	int wantedRes = 0;
	bool fullScreen = false;
	bool setFullScreen = false;
	
	void resizePalette();	
	void getColors(const sf::RenderWindow& window);

	void draw(sf::RenderWindow&);
	void changeResolution(int);

	Button Browse;
	Button Start;
	Button DecRes;
	Button IncRes;
	Button ApplyRes;
	Button Fullscreen;
	Button PickColor;
	Button ApplyColor;
	
	Button palette;

	Button* pressed = nullptr;
	std::vector<Button*> buttons{ &Browse, &Start, &DecRes, &IncRes, &ApplyRes, &Fullscreen, &PickColor, &ApplyColor };

	sf::Sprite background;

	sf::Image paletteImage;
	sf::RectangleShape color;

	sf::Text browseText;
	sf::Text startText;
	sf::Text resolutionText;

	sf::Font font;
	
	//void startInput();

	//sf::Texture 

	sf::Texture buttonTexture;
	sf::Texture pressedButtonTexture;
	sf::Texture leftResolutionTexture;
	sf::Texture pressedleftResolutionTexture;
	sf::Texture rightResolutionTexture;
	sf::Texture pressedrightResolutionTexture;
	sf::Texture ApplyButtonTexture;
	sf::Texture pressedApplyButtonTexture;
	sf::Texture yesFullTexture;
	sf::Texture noFullTexture;
	sf::Texture backgroundTexture;
	sf::Texture paletteTexture;

	std::string TexturePath = "Textures/";
	//int button;
};

	//color picker https://learn.microsoft.com/en-us/cpp/mfc/reference/cmfccolorpickerctrl-class?view=msvc-170