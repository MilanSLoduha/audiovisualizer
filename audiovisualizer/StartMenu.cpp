#include "StartMenu.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Globals.hpp"

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

	if (!font.loadFromFile("font.ttf")) {
		std::cout << "Error loading font" << std::endl;
	}

	BrowseButton.setTexture(buttonTexture);
	BrowseButton.setPosition( width / 10 * 8, height / 10 * 2);
	BrowseButton.setScale(0.04, 0.04);

	StartButton.setTexture(buttonTexture);
	StartButton.setPosition(width / 10 * 8, height / 10 * 8);
	StartButton.setScale(0.04, 0.04);

	browseText.setCharacterSize(width / 64);
	browseText.setFillColor(sf::Color::White);
	browseText.setPosition(width / 10 * 8, height / 10 * 2);
	browseText.setFont(font);
	browseText.setString("Browse");

	startText.setCharacterSize(width / 64);
	startText.setFillColor(sf::Color::White);
	startText.setPosition(width / 10 * 8, height / 10 * 8);
	startText.setFont(font);
	startText.setString("Start");



}

bool StartMenu::clickBrowse(const sf::RenderWindow& window)
{
	return BrowseButton.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)));;
}

bool StartMenu::clickStart(const sf::RenderWindow& window)
{
	return StartButton.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)));;
}

void StartMenu::setPressed(int& button) {
	if (button == 1) {
		BrowseButton.setTexture(pressedButtonTexture);
	}
	else if (button == 2) {
		StartButton.setTexture(pressedButtonTexture);
	}
}

void StartMenu::setUnpressed(int& button) {
	if (button == 1) {
		BrowseButton.setTexture(buttonTexture);
	}
	else if (button == 2) {
		StartButton.setTexture(buttonTexture);
	}
}

void StartMenu::draw(sf::RenderWindow& window)
{
	window.draw(BrowseButton);
	window.draw(StartButton);
	window.draw(browseText);
	window.draw(startText);
}










//int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
//{
//	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED |
//		COINIT_DISABLE_OLE1DDE);
//	if (SUCCEEDED(hr))
//	{
//		IFileOpenDialog* pFileOpen;
//
//		// Create the FileOpenDialog object.
//		hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL,
//			IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));
//
//		if (SUCCEEDED(hr))
//		{
//			// Show the Open dialog box.
//			hr = pFileOpen->Show(NULL);
//
//			// Get the file name from the dialog box.
//			if (SUCCEEDED(hr))
//			{
//				IShellItem* pItem;
//				hr = pFileOpen->GetResult(&pItem);
//				if (SUCCEEDED(hr))
//				{
//					PWSTR pszFilePath;
//					hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);
//
//					// Display the file name to the user.
//					if (SUCCEEDED(hr))
//					{
//						MessageBoxW(NULL, pszFilePath, L"File Path", MB_OK);
//						CoTaskMemFree(pszFilePath);
//					}
//					pItem->Release();
//				}
//			}
//			pFileOpen->Release();
//		}
//		CoUninitialize();
//	}
//	return 0;
//}
//https://learn.microsoft.com/en-us/windows/win32/learnwin32/example--the-open-dialog-box

