//#include "FFT.hpp"
//
//FFT::FFT()
//{
//	if (!music.loadFromFile("caba neblazni.wav"))
//	{
//		std::cout << "Error loading music file" << std::endl;
//	}
//	song.setBuffer(music);
//	song.play();
//
//	samples = music.getSamples();
//	sampleCount = music.getSampleCount();
//	music.getChannelCount();
//
//	fftw_complex in[N], out[N];
//
//	//
//	fftw_plan p = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
//
//	for (int i = 0; i < N; i++)
//	{
//		if (channelCount == 2)
//		{
//			in[i][0] = samples[i];
//			in[i][1] = samples[i + 1];
//		}
//		else if (channelCount == 1)
//		{
//			in[i][0] = samples[i];
//			in[i][1] = 0.0;
//		}
//		std::cout << i << ".  " << in[i][0] << " -- " << in[i][1] << std::endl;
//	}
//
//	//
//	fftw_execute(p);
//	//
//	fftw_destroy_plan(p);
//}