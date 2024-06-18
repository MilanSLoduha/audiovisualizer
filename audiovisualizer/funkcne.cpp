#include "FFT.hpp"
#include <iostream>

FFT::FFT()
{
	if (!music.loadFromFile("test.wav"))
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
	if (done >= sampleCount) return;
	fftw_complex* in = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * N);
	fftw_complex* out = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * N);

	for (int i = 0; i < N; i++)
	{
		if (i + done >= sampleCount) break; // Avoid accessing out of bounds

		if (channelCount == 2)
		{
			in[i][0] = samples[2 * (i + done)]; // Taking left channel for stereo
		}
		else if (channelCount == 1)
		{
			in[i][0] = samples[i + done];
		}
		in[i][1] = 0.0; // Imaginary part is zero
	}
	if (done % 10 == 0)  printf("%lld\n", done / sampleRate);
	done += 2 * N;

	fftw_plan p = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
	fftw_execute(p);

	for (int i = 0; i < N / 2; i++)
	{
		magnitudes[i] = sqrt(out[i][0] * out[i][0] + out[i][1] * out[i][1]);
		//std::cout << magnitudes[i] << std::endl;
		/*std::cout << i << ".  " << magnitudes[i] << std::endl;*/
	}

	

	fftw_destroy_plan(p);
	fftw_free(in);
}
