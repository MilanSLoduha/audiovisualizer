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
	bool clickBrowse(const sf::RenderWindow&);
	bool clickStart(const sf::RenderWindow&);

	sf::Sprite BrowseButton;
	sf::Sprite StartButton;

	sf::Text browseText;
	sf::Text startText;

	sf::Font font;

	void setPressed(int&);
	void setUnpressed(int&);
	void draw(sf::RenderWindow&);

	//void draw(sf::RenderWindow&);
	//void startInput();
	StartMenu();

	sf::Texture buttonTexture;
	sf::Texture pressedButtonTexture;
	sf::Texture backgroundTexture;

	std::string TexturePath;


	bool startMenu;
	int button;
};
