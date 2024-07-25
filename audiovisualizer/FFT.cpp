#include "FFT.hpp"
#include <iostream>

FFT::FFT()
{
//	if (!music.loadFromFile("caba neblazni.wav"))
//	{
//		std::cout << "Error loading music file" << std::endl;
//	}
//	song.setBuffer(music);
//
//	samples_fft = music.getSamples();
//	sampleCount = music.getSampleCount();
//	channelCount = music.getChannelCount();
//	sampleRate = music.getSampleRate();
	magnitudesVirgin = std::vector<double>(N / 2, 0);
	magnitudesOld = std::vector<double>(N / 2, 0);
}

void FFT::applyFFT(const sf::Int16* samples, std::vector<double>& magnitudes)
{
	fftw_complex* in = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * N);
	fftw_complex* out = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * N);

	done = static_cast<long long>(song.getPlayingOffset().asSeconds() * sampleRate); //chats upgrade
	//done += channelCount * static_cast<long long>(N);
	if ((done + N) * channelCount > sampleCount) return;

	for (int i = 0; i < N; i++)
	{
		if (i + done >= sampleCount) break; // Avoid accessing out of bounds

		in[i][0] = samples[channelCount * (i + done)]; // Taking left channel for stereo

		in[i][1] = 0.0; // Imaginary part is zero
	}
	//if (static_cast<int>(round(song.getPlayingOffset().asSeconds() * 10)) % 10 == 0) done = song.getPlayingOffset().asSeconds() * sampleRate;
	//if (done % 10 == 0)  printf("%lld\n", done / sampleRate); // vypisovac casu
	

	//done += channelCount * (N * 0.60);

	fftw_plan p = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
	fftw_execute(p);

	for (int i = 0; i < magnitudes.size(); i++)
	{
		magnitudes[i] = sqrt(out[i][0] * out[i][0] + out[i][1] * out[i][1]);
		magnitudes[i] = magnitudes[i] / 5 / magnitudes.size();//* log10(magnitudes[i] + 1)
		magnitudesVirgin[i] = magnitudes[i];

		if (!smoothing) {//smoothing with other new walue

			long double temp = 0;
			int j = i;
			short rep = 0;

			if (i >= 2) j = i - 2; // i = 3 -> j = 1 or i = 2 -> j = 0
			else j = 0;

			for (j;j < i + 2; j++)
			{
				if (j >= magnitudes.size()) break;
				temp += magnitudesVirgin[j];
				rep++;
			}

			magnitudes[i] = temp / rep;
		}
		if (!smoothing) { //past smoothing
			magnitudes[i] = (magnitudesOld[i] + magnitudes[i]) / 2;
			magnitudesOld[i] = magnitudes[i];
		}
		if (magnitudes[i] > maxMag) magnitudes[i] = maxMag;
	}
	//std::cout << magnitudes.size() << std::endl;



	fftw_destroy_plan(p);
	fftw_free(in);
	fftw_free(out);
}

void FFT::loadMusic(std::string& path)
{	
	/*std::cout << path << std::endl;
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	path = "C:\\Users\\danie\\source\\repos\\audiovisualizer\\audiovisualizer\\èaba òeblázni.mp3";
	//std::string utf8Path = converter.to_bytes(path);*/
	//while (path.find("\\") != std::string::npos) path.replace(path.find("\\"), 1, "/");

	if (path == "NULL") {
		if (!music.loadFromFile("caba neblazni.wav")) {
			std::cout << "error loading music file" << std::endl;
		}
	}
	else {
		if (!music.loadFromFile(std::string(path))) {
			std::cout << "error loading music file" << std::endl;
		}
	}
	song.setBuffer(music);
		
	samples_fft = music.getSamples();
	sampleCount = music.getSampleCount();
	channelCount = music.getChannelCount();
	sampleRate = music.getSampleRate();
}
