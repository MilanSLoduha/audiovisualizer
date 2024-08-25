#pragma once

#include <SFML/Audio.hpp>
#include <fftw3.h>
#include "Globals.hpp"
#include <iostream>
#include <locale>
#include <codecvt>
#include <SFML/Graphics.hpp>
#include <fstream>

class FFT
{
public:
	FFT();
	sf::Sound song;
	void applyFFT(const sf::Int16* samples, std::vector<double>& magnitudes);
	int maxMag; //max magnitude
	sf::SoundBuffer music;
	
	void loadMusic( std::string &path);

	long long done = 0;

	const sf::Int16* samples_fft;

	sf::Uint64 sampleCount;
	unsigned int channelCount;
	unsigned int sampleRate;

	std::vector <double> magnitudesVirgin;
	std::vector <double> magnitudesOld;
	std::vector<double> new_values;

	sf::SoundBufferRecorder recorder;
	std::vector<sf::Int16> recorded;

	int smoothing;
	int smoothingDots = 3; //how many dots will be added between two dots (count + 1)

	void onProcessSamples(const sf::Int16* samples, std::size_t sampleCount);
};