#pragma once


#include <SFML/Graphics.hpp>
#include <shobjidl.h>
#include <Windows.h>


class StartMenu
{
private:
	int selected;
	int max;
public:
	void setSizes();

	int curRes = 0;
	bool fullScreen = false;
	bool setFullScreen = false;

	bool clickBrowse(const sf::RenderWindow&);
	bool clickStart(const sf::RenderWindow&);
	bool clickRightResolution(const sf::RenderWindow& window);
	bool clickLeftResolution(const sf::RenderWindow& window);
	bool clickApply(const sf::RenderWindow& window);
	bool clickYesFull(const sf::RenderWindow& window);

	sf::Sprite BrowseButton;
	sf::Sprite StartButton;
	sf::Sprite leftResolution;
	sf::Sprite rightResolution;
	sf::Sprite ApplyButton;
	sf::Sprite yesFull;

	sf::Sprite background;

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

	std::string TexturePath;


	bool startMenu;
	int button;
};
