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
	sampleRate = music.getSampleRate();
}

void FFT::applyFFT(const sf::Int16* samples, std::vector<double>& magnitudes)
{
	if ((done + N) * channelCount > sampleCount) return;
	fftw_complex* in = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * N);
	fftw_complex* out = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * N);

	for (int i = 0; i < N; i++)
	{
		if (i + done >= sampleCount) break; // Avoid accessing out of bounds

		in[i][0] = samples[channelCount * (i + done)]; // Taking left channel for stereo

		in[i][1] = 0.0; // Imaginary part is zero
	}
	if (static_cast<int>(round(song.getPlayingOffset().asSeconds() * 10)) % 10 == 0) done = song.getPlayingOffset().asSeconds() * sampleRate;
	//if (done % 10 == 0)  printf("%lld\n", done / sampleRate); // vypisovac casu
	done += channelCount * (N * 2);

	fftw_plan p = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
	fftw_execute(p);

	for (int i = 0; i < magnitudes.size(); i++)
	{
		magnitudes[i] = sqrt(out[i][0] * out[i][0] + out[i][1] * out[i][1]);
		//std::cout << magnitudes[i] << std::endl;
		/*std::cout << i << ".  " << magnitudes[i] << std::endl;*/
	}
	//std::cout << magnitudes.size() << std::endl;



	fftw_destroy_plan(p);
	fftw_free(in);
	fftw_free(out);
}
