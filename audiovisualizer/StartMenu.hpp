#pragma once


#include <SFML/Graphics.hpp>
#include <shobjidl.h>
#include <Windows.h>
#include "Globals.hpp"

class StartMenu
{
private:
	int selected;
	int max;
	sf::RenderWindow colorPicker;

public:
	void setSizes();

	int curRes = 0;
	bool fullScreen = false;
	bool setFullScreen = false;
	
	void getColors(const sf::RenderWindow& window);

	bool clickBrowse(const sf::RenderWindow&);
	bool clickStart(const sf::RenderWindow&);
	bool clickRightResolution(const sf::RenderWindow& window);
	bool clickLeftResolution(const sf::RenderWindow& window);
	bool clickApply(const sf::RenderWindow& window);
	bool clickYesFull(const sf::RenderWindow& window);
	bool clickApplyColor(const sf::RenderWindow& window);
	bool clickChooseColor(const sf::RenderWindow& window);

	//color picker https://learn.microsoft.com/en-us/cpp/mfc/reference/cmfccolorpickerctrl-class?view=msvc-170

	sf::Sprite BrowseButton;
	sf::Sprite StartButton;
	sf::Sprite leftResolution;
	sf::Sprite rightResolution;
	sf::Sprite ApplyResolutionButton;
	sf::Sprite yesFull;
	sf::Sprite ChooseColorButton;
	sf::Sprite ApplyColor;
	sf::Sprite palette;

	sf::Sprite background;

	sf::Image paletteImage;
	sf::RectangleShape color;

	sf::Text browseText;
	sf::Text startText;
	sf::Text resolutionText;

	sf::Font font;

	void setPressed(int&);
	void setUnpressed(int&);
	void draw(sf::RenderWindow&);
	void changeResolution(int);

	//void draw(sf::RenderWindow&);
	//void startInput();
	StartMenu();

	sf::Texture buttonTexture;
	sf::Texture pressedButtonTexture;
	sf::Texture backgroundTexture;
	sf::Texture leftResolutionTexture;
	sf::Texture rightResolutionTexture;
	sf::Texture pressedleftResolutionTexture;
	sf::Texture pressedrightResolutionTexture;
	sf::Texture ApplyButtonTexture;
	sf::Texture pressedApplyButtonTexture;
	sf::Texture yesFullTexture;
	sf::Texture noFullTexture;
	sf::Texture paletteTexture;

	std::string TexturePath;


	bool startMenu;
	int button;
};
