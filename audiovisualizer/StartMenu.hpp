#pragma once

#include <SFML/Graphics.hpp>
#include <shobjidl.h>
#include <Windows.h>
#include "Globals.hpp"
#include <codecvt>
#include <locale>
#include <string>
#include <fstream>

class StartMenu
{
private:
	int selected;
	int max;
	sf::RenderWindow colorPicker;

public:
	int actualWidth = width[0];
	int actualHeight = height[0];

	void setSizes();

	int curRes = 0;
	int wantedRes = 0;
	bool fullScreen = false;
	bool setFullScreen = false;
	
	void resizePalette();	
	void getColors(const sf::RenderWindow& window);

	bool clickBrowse(const sf::RenderWindow&);
	bool clickStart(const sf::RenderWindow&);
	bool clickRightResolution(const sf::RenderWindow& window);
	bool clickLeftResolution(const sf::RenderWindow& window);
	bool clickApply(const sf::RenderWindow& window);
	bool clickYesFull(const sf::RenderWindow& window);
	bool clickApplyColor(const sf::RenderWindow& window);
	bool clickChooseColor(const sf::RenderWindow& window);

	void browseFile();

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

	sf::Sprite formMin;
	sf::Sprite formMax;
	sf::Sprite formXbegin;
	sf::Sprite formYbegin;
	sf::Sprite formXend;
	sf::Sprite formMaxMag;
	/*sf::Sprite formYend;*/

	bool formMinSelected;
	bool formMaxSelected;
	bool formXbeginSelected;
	bool formYbeginSelected;
	bool formXendSelected;
	/*bool formYendSelected;*/
	bool formMaxMagSelected;

	bool clikedFormMin(const sf::RenderWindow& window);
	bool clikedFormMax(const sf::RenderWindow& window);
	bool clikedFormXbegin(const sf::RenderWindow& window);
	bool clikedFormYbegin(const sf::RenderWindow& window);
	bool clikedFormXend(const sf::RenderWindow& window);
	//bool clikedFormYend(const sf::RenderWindow& window);
	bool clikedFormMaxMag(const sf::RenderWindow& window);

	sf::Text formMinText;
	sf::Text formMaxText;
	sf::Text formXbeginText;
	sf::Text formYbeginText;
	sf::Text formXendText;
	//sf::Text formYendText;
	sf::Text formMaxMagText;

	std::string formMinString;
	std::string formMaxString;
	std::string xbeginString;
	std::string xendString;
	std::string ybeginString;
	/*std::string yendString;*/
	std::string maxMagString;

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

	std::string getName(std::string&);

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
	sf::Texture formTexture;

	std::string TexturePath;

	std::string MusicPath = "NULL";
	std::string BackgroundPath;
	std::string backgroundName;
	std::string musicName;

	sf::Text backgroundText;
	sf::Text musicText;

	bool startMenu;
	int button;
};
