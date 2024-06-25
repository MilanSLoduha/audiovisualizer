#include "StartMenu.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>

StartMenu::StartMenu()
{
	TexturePath = "Textures/";
	selected = 0;
	max = 2;
	startMenu = true;

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

	BrowseButton.setTexture(buttonTexture);
	BrowseButton.setPosition( width[curRes] / 10 * 8, height[curRes] / 10 * 2);
	BrowseButton.setScale(width[curRes] / 48000., width[curRes] / 48000.);

	StartButton.setTexture(buttonTexture);
	StartButton.setPosition(width[curRes] / 10 * 8, height[curRes] / 10 * 8);
	StartButton.setScale(width[curRes] / 48000., width[curRes] / 48000.);

	browseText.setCharacterSize(width[curRes] / 64);
	browseText.setFillColor(sf::Color::White);
	browseText.setPosition(width[curRes] / 10 * 8, height[curRes] / 10 * 2);
	browseText.setFont(font);
	browseText.setString("Browse");

	startText.setCharacterSize(width[curRes] / 64);
	startText.setFillColor(sf::Color::White);
	startText.setPosition(width[curRes] / 10 * 8, height[curRes] / 10 * 8);
	startText.setFont(font);
	startText.setString("Start");

	leftResolution.setTexture(leftResolutionTexture);
	leftResolution.setPosition(width[curRes] / 10 * 7.6, height[curRes] / 10 * 3);
	leftResolution.setScale(width[curRes] / 4800., width[curRes] / 4800.);

	rightResolution.setTexture(rightResolutionTexture);
	rightResolution.setPosition(width[curRes] / 10 * 9.2, height[curRes] / 10 * 3);
	rightResolution.setScale(width[curRes] / 4800., width[curRes] / 4800.);

	ApplyResolutionButton.setTexture(ApplyButtonTexture);
	ApplyResolutionButton.setPosition(width[curRes] / 10 * 6.4, height[curRes] / 10 * 3);
	ApplyResolutionButton.setScale(width[curRes] / 4800., width[curRes] / 4800.);

	background.setTexture(backgroundTexture);
	background.setScale(width[curRes] / 1920., width[curRes] / 1920.);

	resolutionText.setCharacterSize(width[curRes] / 64);
	resolutionText.setFillColor(sf::Color::Cyan);
	resolutionText.setOutlineColor(sf::Color::Black);
	resolutionText.setOutlineThickness(2);
	resolutionText.setPosition(width[curRes] / 10 * 8.2, height[curRes] / 10 * 3.3);
	resolutionText.setFont(font);
	resolutionText.setString(std::to_string(width[curRes]) + "x" + std::to_string(height[curRes]));

	yesFull.setTexture(noFullTexture);
	yesFull.setPosition(width[curRes] / 10 * 7, height[curRes] / 10 * 3);
	yesFull.setScale(width[curRes] / 4800., width[curRes] / 4800.);

	ChooseColorButton.setTexture(ApplyButtonTexture);
	ChooseColorButton.setPosition(width[curRes] / 10 * 7, height[curRes] / 10 * 4.2);
	ChooseColorButton.setScale(width[curRes] / 4800., width[curRes] / 4800.);

	ApplyColor.setTexture(ApplyButtonTexture);
	ApplyColor.setPosition(width[curRes] / 10 * 6.4, height[curRes] / 10 * 4.2);
	ApplyColor.setScale(width[curRes] / 4800., width[curRes] / 4800.);


	palette.setTexture(paletteTexture);
	palette.setPosition(width[curRes] / 10 * 8, height[curRes] / 10 * 4);
	palette.setScale(0.63,0.63);
	//palette.setSize(sf::Vector2f(width[curRes] / 6.5, width[curRes] / 6.5));


	color.setSize(sf::Vector2f(width[curRes] / 23, width[curRes] / 23));
	color.setFillColor(sf::Color::White);
	color.setOutlineColor(sf::Color::Black);
	color.setOutlineThickness(2);
	color.setPosition(width[curRes] / 10 * 9.55, height[curRes] / 10 * 4.03);

}

void StartMenu::getColors(const sf::RenderWindow& window)
{
	sf::Vector2f localPos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)) - palette.getPosition();
	color.setFillColor(paletteImage.getPixel(localPos.x * 1.59, localPos.y * 1.59));
}

void StartMenu::setSizes()
{
	palette.setPosition(width[curRes] / 10 * 8, height[curRes] / 10 * 4);
	palette.setScale(0.63, 0.63);

	color.setPosition(width[curRes] / 10 * 9.55, height[curRes] / 10 * 4.03);
	color.setSize(sf::Vector2f(width[curRes] / 23, width[curRes] / 23));

	BrowseButton.setPosition(width[curRes] / 10 * 8, height[curRes] / 10 * 2);
	BrowseButton.setScale(width[curRes] / 48000., width[curRes] / 48000.);

	StartButton.setPosition(width[curRes] / 10 * 8, height[curRes] / 10 * 8);
	StartButton.setScale(width[curRes] / 48000., width[curRes] / 48000.);

	browseText.setCharacterSize(width[curRes] / 64);
	browseText.setPosition(width[curRes] / 10 * 8, height[curRes] / 10 * 2);

	startText.setCharacterSize(width[curRes] / 64);
	startText.setPosition(width[curRes] / 10 * 8, height[curRes] / 10 * 8);

	leftResolution.setPosition(width[curRes] / 10 * 7.6, height[curRes] / 10 * 3);
	leftResolution.setScale(width[curRes] / 4800., width[curRes] / 4800.);

	rightResolution.setPosition(width[curRes] / 10 * 9.2, height[curRes] / 10 * 3);
	rightResolution.setScale(width[curRes] / 4800., width[curRes] / 4800.);

	ApplyResolutionButton.setPosition(width[curRes] / 10 * 6.4, height[curRes] / 10 * 3);
	ApplyResolutionButton.setScale(width[curRes] / 4800., width[curRes] / 4800.);

	background.setScale(width[curRes] / 1920., height[curRes] / 1080.);

	resolutionText.setCharacterSize(width[curRes] / 64);
	resolutionText.setPosition(width[curRes] / 10 * 8.2, height[curRes] / 10 * 3.3);

	yesFull.setPosition(width[curRes] / 10 * 7, height[curRes] / 10 * 3);
	yesFull.setScale(width[curRes] / 4800., width[curRes] / 4800.);

	ChooseColorButton.setPosition(width[curRes] / 10 * 6.4, height[curRes] / 10 * 5);
	ChooseColorButton.setScale(width[curRes] / 4800., width[curRes] / 4800.);

	ApplyColor.setPosition(width[curRes] / 10 * 6.4, height[curRes] / 10 * 6);
	ApplyColor.setScale(width[curRes] / 4800., width[curRes] / 4800.);
}

bool StartMenu::clickBrowse(const sf::RenderWindow& window)
{
	return BrowseButton.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)));;
}

bool StartMenu::clickStart(const sf::RenderWindow& window)
{
	return StartButton.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)));;
}

bool StartMenu::clickLeftResolution(const sf::RenderWindow& window)
{
	return leftResolution.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)));;
}

bool StartMenu::clickRightResolution(const sf::RenderWindow& window)
{
	return rightResolution.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)));;
}

bool StartMenu::clickApply(const sf::RenderWindow& window)
{
	return ApplyResolutionButton.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)));;
}

bool StartMenu::clickYesFull(const sf::RenderWindow& window)
{
	return yesFull.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)));;
}

bool StartMenu::clickApplyColor(const sf::RenderWindow& window)
{
	return ApplyColor.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)));;
}

bool StartMenu::clickChooseColor(const sf::RenderWindow& window)
{
	return ChooseColorButton.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)));;
}

void StartMenu::setPressed(int& button) {
	if (button == 1) {
		BrowseButton.setTexture(pressedButtonTexture);
	}
	else if (button == 2) {
		StartButton.setTexture(pressedButtonTexture);
	}
	else if (button == 3) {
		leftResolution.setTexture(pressedleftResolutionTexture);
	}
	else if (button == 4) {
		rightResolution.setTexture(pressedrightResolutionTexture);
	}
	else if (button == 5) {
		ApplyResolutionButton.setTexture(pressedApplyButtonTexture);
	}
	else if (button == 6) {
		yesFull.setTexture(yesFullTexture);
	}
	else if (button == 7) {
		ChooseColorButton.setTexture(pressedApplyButtonTexture);
	}
	else if (button == 8) {
		ApplyColor.setTexture(pressedApplyButtonTexture);
	}
}

void StartMenu::setUnpressed(int& button) {
	if (button == 1) {
		BrowseButton.setTexture(buttonTexture);
	}
	else if (button == 2) {
		StartButton.setTexture(buttonTexture);
	}
	else if (button == 3) {
		leftResolution.setTexture(leftResolutionTexture);
	}
	else if (button == 4) {
		rightResolution.setTexture(rightResolutionTexture);
	}
	else if (button == 5) {
		ApplyResolutionButton.setTexture(ApplyButtonTexture);
	}
	else if (button == 6) {
		yesFull.setTexture(noFullTexture);
	}
	else if (button == 7) {
		ChooseColorButton.setTexture(ApplyButtonTexture);
	}
	else if (button == 8) {
		ApplyColor.setTexture(ApplyButtonTexture);
	}
}

void StartMenu::draw(sf::RenderWindow& window)
{
	window.draw(background);
	window.draw(BrowseButton);
	window.draw(StartButton);
	window.draw(browseText);
	window.draw(startText);
	window.draw(leftResolution);
	window.draw(rightResolution);
	window.draw(ApplyResolutionButton);
	window.draw(resolutionText);
	window.draw(yesFull);
	window.draw(ChooseColorButton);
	window.draw(ApplyColor);
	window.draw(palette);
	window.draw(color);
}

void StartMenu::changeResolution(int diff)
{
	if (diff == 1) {
		curRes++;
		if (curRes >= width.size()) curRes = 0;
	}
	else if (diff == -1) {
		curRes--;
		if (curRes < 0) curRes = width.size() - 1;
	}
	resolutionText.setString(std::to_string(width[curRes]) + "x" + std::to_string(height[curRes]));

}










//////int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
//////{
//////	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED |
//////		COINIT_DISABLE_OLE1DDE);
//////	if (SUCCEEDED(hr))
//////	{
//////		IFileOpenDialog* pFileOpen;
//////
//////		// Create the FileOpenDialog object.
//////		hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL,
//////			IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));
//////
//////		if (SUCCEEDED(hr))
//////		{
//////			// Show the Open dialog box.
//////			hr = pFileOpen->Show(NULL);
//////
//////			// Get the file name from the dialog box.
//////			if (SUCCEEDED(hr))
//////			{
//////				IShellItem* pItem;
//////				hr = pFileOpen->GetResult(&pItem);
//////				if (SUCCEEDED(hr))
//////				{
//////					PWSTR pszFilePath;
//////					hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);
//////
//////					// Display the file name to the user.
//////					if (SUCCEEDED(hr))
//////					{
//////						MessageBoxW(NULL, pszFilePath, L"File Path", MB_OK);
//////						CoTaskMemFree(pszFilePath);
//////					}
//////					pItem->Release();
//////				}
//////			}
//////			pFileOpen->Release();
//////		}
//////		CoUninitialize();
//////	}
//////	return 0;
//////}
//https://learn.microsoft.com/en-us/windows/win32/learnwin32/example--the-open-dialog-box

