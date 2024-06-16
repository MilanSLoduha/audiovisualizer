#include "FFT.hpp"
#include <iostream>

FFT::FFT()
{
	if (!music.loadFromFile("caba neblazni.wav"))
	{
		std::cout << "Error loading music file" << std::endl;
	}
	song.setBuffer(music);
	song.play();

	samples_fft = music.getSamples();
	sampleCount = music.getSampleCount();
	channelCount = music.getChannelCount();
	magnitudes.resize(N / 2);

	std::cout << sampleCount << "\n";
	for (int i = 0; i < sampleCount; i++) {
		std::cout << i << ". " << samples_fft[i] << "\n";
	}
	std::cout << "------------\n";
}

void FFT::applyFFT(const sf::Int16* samples, std::vector<double>& magnitudes)
{
	fftw_complex* in = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * N);
	fftw_complex* out = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * N);
	fftw_plan p = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);

	for (int i = 0; i < N; i++)
	{
		if (channelCount == 2)
		{
			in[i][0] = samples[i];
			in[i][1] = samples[i + 1];
		}
		else if (channelCount == 1)
		{
			in[i][0] = samples[i];
			in[i][1] = 0.0;
		}
		std::cout << i << ".  " << in[i][0] << " -- " << in[i][1] << std::endl;
	}

	fftw_execute(p);

	for (int i = 0; i < N / 2; i++)
	{
		magnitudes[i] = sqrt(out[i][0] * out[i][0] + out[i][1] * out[i][1]);
		std::cout << i << ".  " << magnitudes[i] << std::endl;
	}

	fftw_destroy_plan(p);
	fftw_free(in);
	fftw_free(out);
}
