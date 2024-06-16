#pragma once

#include <SFML/Audio.hpp>
#include <fftw3.h>
#include "Globals.hpp"
#include <iostream>

class FFT
{
public:
	FFT();
	sf::Sound song;
	void applyFFT(const sf::Int16* samples, std::vector<double>& magnitudes);
	sf::SoundBuffer music;
	
	std::vector<double> magnitudes;

private:
	static const int N = 1024; // 1024 samples for the FFT - 1024 / 44100 = 0.023 seconds -- values 2^n
	const sf::Int16* samples;
	sf::Uint64 sampleCount;
	unsigned int channelCount;
};