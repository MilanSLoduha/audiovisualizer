#include "FFT.hpp"

FFT::FFT()
{
	if (!music.loadFromFile("caba neblazni.wav"))
	{
		std::cout << "Error loading music file" << std::endl;
	}
	song.setBuffer(music);
	song.play();
}