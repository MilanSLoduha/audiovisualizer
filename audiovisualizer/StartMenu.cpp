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
		if (!formTexture.loadFromFile(TexturePath + "text.png")) {
			std::cout << "Error loading palette texture" << std::endl;
		}
		if (!offTexture.loadFromFile(TexturePath + "off.png")) {
			std::cout << "Error loading off texture" << std::endl;
		}
		if (!midTexture.loadFromFile(TexturePath + "mid.png")) {
			std::cout << "Error loading mid texture" << std::endl;
		}
		if (!highTexture.loadFromFile(TexturePath + "high.png")) {
			std::cout << "Error loading high texture" << std::endl;
		}
		if (!upTexture.loadFromFile(TexturePath + "up.png")) {
			std::cout << "Error loading up texture" << std::endl;
		}
		if (!downTexture.loadFromFile(TexturePath + "down.png")) {
			std::cout << "Error loading down texture" << std::endl;
		}
		if (!upDownTexture.loadFromFile(TexturePath + "upDown.png")) {
			std::cout << "Error loading upDown texture" << std::endl;
		}

		if (!font.loadFromFile("Roboto-Regular.ttf")) {
			std::cout << "Error loading font" << std::endl;
		}
	}

	sf::Texture texture[3] = { formTexture, yesFullTexture, noFullTexture };
	smoothingTextures = { offTexture, midTexture, highTexture };
	sideTextures = { upTexture, downTexture, upDownTexture };

	BrowseButton.setTexture(buttonTexture);

	StartButton.setTexture(buttonTexture);

	browseText.setFillColor(sf::Color::White);
	browseText.setFont(font);
	browseText.setString("Browse");

	startText.setFillColor(sf::Color::White);
	startText.setFont(font);
	startText.setString("Start");

	leftResolution.setTexture(leftResolutionTexture);

	rightResolution.setTexture(rightResolutionTexture);

	ApplyResolutionButton.setTexture(ApplyButtonTexture);

	background.setTexture(backgroundTexture);

	formName.setFillColor(sf::Color::Cyan);
	formName.setOutlineColor(sf::Color::Black);
	formName.setOutlineThickness(2);
	formName.setFont(font);
	formName.setString(forms[wantedForm]);

	yesFull.setTexture(noFullTexture);

	ChooseColorButton.setTexture(ApplyButtonTexture);

	ApplyColor.setTexture(ApplyButtonTexture);

	palette.setTexture(paletteTexture);
	//palette.setScale(0.63,0.63);
	//palette.setSize(sf::Vector2f(width[curRes] / 6.5, width[curRes] / 6.5));


	color.setFillColor(sf::Color::White);
	color.setOutlineColor(sf::Color::Black);
	color.setOutlineThickness(2);
	
	musicText.setString("Default music selected");
	musicText.setFillColor(sf::Color::White);
	musicText.setFont(font);

	backgroundText.setString("Default background selected");
	backgroundText.setFillColor(sf::Color::White);
	backgroundText.setFont(font);

	formMax.setTexture(formTexture);
	formMin.setTexture(formTexture);

	xbeginString = "0";
	formXbeginText.setFillColor(sf::Color::Blue);
	formXbeginText.setString(xbeginString);
	formXbeginText.setFont(font);
	formXbeginText.setOrigin(formXbeginText.getGlobalBounds().width / 2, formXbeginText.getGlobalBounds().height / 2);

	ybeginString = "0";
	formYbeginText.setFillColor(sf::Color::Cyan);
	formYbeginText.setString(ybeginString);
	formYbeginText.setFont(font);

	xendString = "Default";
	formXendText.setFillColor(sf::Color::Green);
	formXendText.setString(xendString);
	formXendText.setFont(font);

	/*yendString = "Default";
	formYendText.setFillColor(sf::Color::Black);
	formYendText.setString(yendString);
	formYendText.setFont(font);*/

	maxMagString = "Off";
	formMaxMagText.setFillColor(sf::Color::Magenta);
	formMaxMagText.setString(maxMagString);
	formMaxMagText.setFont(font);

	formMaxText.setFillColor(sf::Color::Black);
	formMinText.setFillColor(sf::Color::Black);
	formMinString = "Default";
	formMaxString = "Default";
	formMaxText.setFont(font);
	formMinText.setFont(font);
	formMaxText.setString(formMaxString);
	formMinText.setString(formMinString);

	formMaxMag.setTexture(formTexture);
	formXbegin.setTexture(formTexture);
	formYbegin.setTexture(formTexture);
	formXend.setTexture(formTexture);
	//formYend.setTexture(formTexture);

	Form.setTexture(formTexture);

	FormText.setFillColor(sf::Color::Black);
	FormText.setFont(font);
	FormText.setString(formStrings[wantedForm]);

	resizePalette();
	setSizes();
}

void StartMenu::resizePalette()
{
	palette.setPosition(actualWidth / 10 * 8, actualHeight / 10 * 4);
	//palette.setScale(actualWidth / 1920. * 1.26, actualHeight / 1360.8);
	palette.setScale(actualWidth / 1920. * 1.26, actualWidth / 1920. * 1.26);

	color.setPosition(actualWidth / 10 * 9.55, actualHeight / 10 * 4.03);
	//color.setSize(sf::Vector2f(actualWidth / 23, actualHeight / 12.94));
	color.setSize(sf::Vector2f(actualWidth / 23, actualWidth / 23));
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

	formName.setCharacterSize(actualWidth / 64);
	formName.setPosition(actualWidth / 10 * 8.2, actualHeight / 10 * 2.7); //3.3

	Form.setPosition(actualWidth / 10 * 8.16, actualHeight / 10 * 3.15);
	Form.setScale(actualWidth / 12000., actualHeight / 9000.);

	FormText.setCharacterSize(actualWidth / 64);
	FormText.setPosition(actualWidth / 10 * 8.3, actualHeight / 10 * 3.3);

	yesFull.setPosition(actualWidth / 10 * 7, actualHeight / 10 * 3);
	yesFull.setScale(actualWidth / 4800., actualHeight / 2700.);

	ChooseColorButton.setPosition(actualWidth / 10 * 6.4, actualHeight / 10 * 5);
	ChooseColorButton.setScale(actualWidth / 4800., actualHeight / 2700.);

	ApplyColor.setPosition(actualWidth / 10 * 6.4, actualHeight / 10 * 6);
	ApplyColor.setScale(actualWidth / 4800., actualHeight / 2700.);

	formMax.setPosition(actualWidth / 10 * 7.6, actualHeight / 10 * 7);
	formMax.setScale(actualWidth / 12000., actualHeight / 9000.);

	formMin.setPosition(actualWidth / 10 * 6.4, actualHeight / 10 * 7);
	formMin.setScale(actualWidth / 12000., actualHeight / 9000.);

	formMinText.setCharacterSize(actualWidth / 64);
	formMinText.setPosition(actualWidth / 10 * 6.5, actualHeight / 10 * 7.3);;

	formMaxText.setCharacterSize(actualWidth / 64);
	formMaxText.setPosition(actualWidth / 10 * 7.7, actualHeight / 10 * 7.3);

	formXbegin.setPosition(actualWidth / 10 * 4.4, actualHeight / 10 * 4);
	formXbegin.setScale(actualWidth / 12000., actualHeight / 9000.);
	formXbeginText.setCharacterSize(actualWidth / 64);
	formXbeginText.setPosition(actualWidth / 10 * 4.5, actualHeight / 10 * 4.3);
	
	formYbegin.setPosition(actualWidth / 10 * 5.6, actualHeight / 10 * 4);
	formYbegin.setScale(actualWidth / 12000., actualHeight / 9000.);
	formYbeginText.setCharacterSize(actualWidth / 64);
	formYbeginText.setPosition(actualWidth / 10 * 5.7, actualHeight / 10 * 4.3);
	
	formXend.setPosition(actualWidth / 10 * 4.4, actualHeight / 10 * 5);
	formXend.setScale(actualWidth / 12000., actualHeight / 9000.);
	formXendText.setCharacterSize(actualWidth / 64);
	formXendText.setPosition(actualWidth / 10 * 4.5, actualHeight / 10 * 5.3);
	/*
	formYend.setPosition(actualWidth / 10 * 7.6, actualHeight / 10 * 5);
	formYend.setScale(actualWidth / 12000., actualHeight / 9000.);
	formYendText.setCharacterSize(actualWidth / 64);
	formYendText.setPosition(actualWidth / 10 * 7.7, actualHeight / 10 * 5.3);*/

	formMaxMag.setPosition(actualWidth / 10 * 4.4, actualHeight / 10 * 6);
	formMaxMag.setScale(actualWidth / 12000., actualHeight / 9000.);
	formMaxMagText.setCharacterSize(actualWidth / 64);
	formMaxMagText.setPosition(actualWidth / 10 * 4.5, actualHeight / 10 * 6.3);

}

	bool StartMenu::clickBrowse(const sf::RenderWindow & window)
	{
		return BrowseButton.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)));;
	}

	bool StartMenu::clickStart(const sf::RenderWindow & window)
	{
		return StartButton.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)));;
	}

	bool StartMenu::clickLeftResolution(const sf::RenderWindow & window)
	{
		return leftResolution.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)));;
	}

	bool StartMenu::clickRightResolution(const sf::RenderWindow & window)
	{
		return rightResolution.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)));;
	}

	bool StartMenu::clickApply(const sf::RenderWindow & window)
	{
		return ApplyResolutionButton.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)));;
	}

	bool StartMenu::clickYesFull(const sf::RenderWindow & window)
	{
		return yesFull.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)));;
	}

	bool StartMenu::clickApplyColor(const sf::RenderWindow & window)
	{
		return ApplyColor.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)));;
	}

	bool StartMenu::clickChooseColor(const sf::RenderWindow & window)
	{
		return ChooseColorButton.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)));;
	}

	bool StartMenu::clikedFormMax(const sf::RenderWindow & window)
	{
		return formMax.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
	}

	bool StartMenu::clikedFormMin(const sf::RenderWindow & window)
	{
		return formMin.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
	}

	bool StartMenu::clikedFormXbegin(const sf::RenderWindow & window)
	{
		return formXbegin.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
	}

	bool StartMenu::clikedFormYbegin(const sf::RenderWindow & window)
	{
		return formYbegin.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
	}

	bool StartMenu::clikedFormXend(const sf::RenderWindow & window)
	{
		return formXend.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
	}

	//bool StartMenu::clikedFormYend(const sf::RenderWindow & window)
	//{
	//	return formYend.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
	//}

	bool StartMenu::clikedFormMaxMag(const sf::RenderWindow & window)
	{
		return formMaxMag.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
	}

	bool StartMenu::clikedForm(const sf::RenderWindow& window)
	{
		return Form.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
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
}

std::string StartMenu::getName(std::string& path)
{
	size_t pos = path.find_last_of("/\\");
	std::string result = path.substr(pos == std::string::npos ? 0 : pos + 1);
	return result;
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
	window.draw(formName);
	window.draw(Form);
	window.draw(FormText);
	
	window.draw(yesFull);
	window.draw(palette);
	window.draw(color);
	window.draw(backgroundText);
	window.draw(musicText);

	window.draw(formMax);	
	window.draw(formMin);
	window.draw(formMaxText);
	window.draw(formMinText);
	window.draw(formXbegin);
	window.draw(formYbegin);
	window.draw(formXend);
	//window.draw(formYend);
	window.draw(formMaxMag);
	window.draw(formXbeginText);
	window.draw(formYbeginText);
	window.draw(formXendText);
	//window.draw(formYendText);
	window.draw(formMaxMagText);
}

void StartMenu::changeForm(int diff)
{
	if (diff == 1) {
		wantedForm++;
		if (wantedForm >= formsSize) wantedForm = 0;
	}
	else if (diff == -1) {
		wantedForm--;
		if (wantedForm < 0) wantedForm = formsSize - 1;
	}
	formName.setString(forms[wantedForm]);
	FormText.setString(formStrings[wantedForm]);
	if (wantedForm == 8) {
		Form.setTexture(smoothingTextures[selectedSmoothing]);
	}
	else if (wantedForm == 9) {
		Form.setTexture(sideTextures[selectedSide]);
	}
	else {
		Form.setTexture(formTexture);
	}
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
		path = utf16_to_utf8(shortFilePath);
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
