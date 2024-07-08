#include "StartMenu.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>

StartMenu::StartMenu()
{
	TexturePath = "Textures/";
	selected = 0;
	max = 2;
	startMenu = true;

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
	palette.setScale(width[curRes] / 1920. * 1.26, width[curRes] / 1920. * 1.26);
	//palette.setScale(0.63,0.63);
	//palette.setSize(sf::Vector2f(width[curRes] / 6.5, width[curRes] / 6.5));


	color.setSize(sf::Vector2f(width[curRes] / 23, width[curRes] / 23));
	color.setFillColor(sf::Color::White);
	color.setOutlineColor(sf::Color::Black);
	color.setOutlineThickness(2);
	color.setPosition(width[curRes] / 10 * 9.55, height[curRes] / 10 * 4.03);
	
	musicText.setString("Default music selected");
	musicText.setCharacterSize(width[curRes] / 64);
	musicText.setFillColor(sf::Color::White);
	musicText.setPosition(width[curRes] / 10 * 6, height[curRes] / 10 * 1);
	musicText.setFont(font);

	backgroundText.setString("Default background selected");
	backgroundText.setCharacterSize(width[curRes] / 64);
	backgroundText.setFillColor(sf::Color::White);
	backgroundText.setPosition(width[curRes] / 10 * 6, height[curRes] / 10 * 1.3);
	backgroundText.setFont(font);
}

void StartMenu::resizePalette()
{
	palette.setPosition(actualWidth / 10 * 8, actualHeight / 10 * 4);
	palette.setScale(actualWidth / 1920. * 1.26, actualHeight / 1360.8);

	color.setPosition(actualWidth / 10 * 9.55, actualHeight / 10 * 4.03);
	color.setSize(sf::Vector2f(actualWidth / 23, actualHeight / 12.94));
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
	musicText.setCharacterSize(actualWidth / 64);
	musicText.setPosition(actualWidth / 10 * 6, actualHeight / 10 * 1);

	backgroundText.setCharacterSize(actualWidth / 64);
	backgroundText.setPosition(actualWidth / 10 * 6, actualHeight / 10 * 1.3);

	BrowseButton.setPosition(actualWidth / 10 * 8, actualHeight / 10 * 2);
	BrowseButton.setScale(actualWidth / 48000., actualHeight / 27000.);

	StartButton.setPosition(actualWidth / 10 * 8, actualHeight / 10 * 8);
	StartButton.setScale(actualWidth / 48000., actualHeight / 27000.);

	browseText.setCharacterSize(actualWidth / 64);
	browseText.setPosition(actualWidth / 10 * 8, actualHeight / 10 * 2);

	startText.setCharacterSize(actualWidth / 64);
	startText.setPosition(actualWidth / 10 * 8, actualHeight / 10 * 8);

	leftResolution.setPosition(actualWidth / 10 * 7.6, actualHeight / 10 * 3);
	leftResolution.setScale(actualWidth / 4800., actualHeight / 2700.);

	rightResolution.setPosition(actualWidth / 10 * 9.2, actualHeight / 10 * 3);
	rightResolution.setScale(actualWidth / 4800., actualHeight / 2700.);

	ApplyResolutionButton.setPosition(actualWidth / 10 * 6.4, actualHeight / 10 * 3);
	ApplyResolutionButton.setScale(actualWidth / 4800., actualHeight / 2700.);

	background.setScale(actualWidth / 1920., actualHeight / 1080.);

	resolutionText.setCharacterSize(actualWidth / 64);
	resolutionText.setPosition(actualWidth / 10 * 8.2, actualHeight / 10 * 3.3);

	yesFull.setPosition(actualWidth / 10 * 7, actualHeight / 10 * 3);
	yesFull.setScale(actualWidth / 4800., actualHeight / 2700.);

	ChooseColorButton.setPosition(actualWidth / 10 * 6.4, actualHeight / 10 * 5);
	ChooseColorButton.setScale(actualWidth / 4800., actualHeight / 2700.);

	ApplyColor.setPosition(actualWidth / 10 * 6.4, actualHeight / 10 * 6);
	ApplyColor.setScale(actualWidth / 4800., actualHeight / 2700.);
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

std::string StartMenu::getName(std::string& path)
{
	int pos = 0;
	if(path.find('\\')) pos  = path.find_last_of('\\');
	else if (path.find('/')) pos = path.find_last_of('/');
	return path.substr(pos + 1);
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
	window.draw(backgroundText);
	window.draw(musicText);
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


std::string utf16_to_utf8(const std::wstring& utf16_string) {
	int utf8_length = WideCharToMultiByte(CP_UTF8, 0, utf16_string.c_str(), -1, nullptr, 0, nullptr, nullptr);
	std::string utf8_string(utf8_length, 0);
	WideCharToMultiByte(CP_UTF8, 0, utf16_string.c_str(), -1, &utf8_string[0], utf8_length, nullptr, nullptr);
	return utf8_string;
}

void StartMenu::browseFile() {
	wchar_t szFilePath[MAX_PATH] = { 0 };  // file path string buffer
	COMDLG_FILTERSPEC imgfiles[3] = { {L"Music Files", L"*.mp3;*.wav;"},
									  {L"Image Files", L"*.jpg;*.png;*.bmp;*.tif"},
									  {L"All Files", L"*.*"} };  // file types to be displayed

	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
	if (SUCCEEDED(hr)) {
		IFileOpenDialog* pFileOpen = NULL;

		// Create the FileOpenDialog object.
		hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL, IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));
		if (SUCCEEDED(hr)) {
			// Show the Open dialog box.
			pFileOpen->SetFileTypes(3, imgfiles);  // choose file types to be displayed
			pFileOpen->SetTitle(L"Open File");     // heading of dialog box
			hr = pFileOpen->Show(GetForegroundWindow());

			// Get the file name from the dialog box.
			if (SUCCEEDED(hr)) {
				IShellItem* pItem;
				hr = pFileOpen->GetResult(&pItem);
				if (SUCCEEDED(hr)) {
					LPWSTR pTemp;
					hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pTemp);
					if (SUCCEEDED(hr)) {
						wcsncpy_s(szFilePath, pTemp, _TRUNCATE);
						CoTaskMemFree(pTemp);
					}
					pItem->Release();
				}
			}
			pFileOpen->Release();
		}
		CoUninitialize();
	}

	std::string path;

	wchar_t shortPath[MAX_PATH] = { 0 };
	if (GetShortPathName(szFilePath, shortPath, MAX_PATH)) {
		std::wstring shortFilePath(shortPath);
		std::string shortUtf8Path = utf16_to_utf8(shortFilePath);
		path = shortUtf8Path;
	}

	std::string utf8Input = utf16_to_utf8(szFilePath);

	if (utf8Input.find(".mp3") != std::string::npos || utf8Input.find(".wav") != std::string::npos) {
		MusicPath = path;
		musicName = getName(utf8Input);
		musicText.setString(musicName);
	}
	else if (utf8Input.find(".jpg") != std::string::npos || utf8Input.find(".png") != std::string::npos ||
		utf8Input.find(".bmp") != std::string::npos || utf8Input.find(".tif") != std::string::npos) {
		BackgroundPath = path;
		backgroundName = getName(utf8Input);
		backgroundText.setString(backgroundName);
	}
}

//https://learn.microsoft.com/en-us/windows/win32/learnwin32/example--the-open-dialog-box
//https://cplusplus.com/forum/windows/275617/
