#pragma once

#include <SFML/Audio.hpp>
#include <fftw3.h>
#include "Globals.hpp"
#include <iostream>
#include <locale>
#include <codecvt>
#include <SFML/Graphics.hpp>

class FFT
{
public:
	//FFT();
	sf::Sound song;
	void applyFFT(const sf::Int16* samples, std::vector<double>& magnitudes);
	sf::SoundBuffer music;
	
	void loadMusic( std::wstring &path);

	long long done = 0;

	const sf::Int16* samples_fft;

	sf::Uint64 sampleCount;
	unsigned int channelCount;
	unsigned int sampleRate;

private:
	
};