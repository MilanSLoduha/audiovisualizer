//#include <SFML/Audio.hpp>
//#include <SFML/Graphics.hpp>
//#include <fftw3.h>
//#include <iostream>
//#include <vector>
//#include <cmath>
//
//const int SAMPLE_RATE = 44100;
//const int FFT_SIZE = 1024;
//const int WINDOW_WIDTH = 800;
//const int WINDOW_HEIGHT = 600;
//
//void applyFFT(const std::vector<sf::Int16>& samples, std::vector<double>& magnitudes) {
//    fftw_complex* in = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * FFT_SIZE);
//    fftw_complex* out = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * FFT_SIZE);
//    fftw_plan p = fftw_plan_dft_1d(FFT_SIZE, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
//
//    for (int i = 0; i < FFT_SIZE; ++i) {
//        in[i][0] = samples[i]; // real part
//        in[i][1] = 0.0;        // imaginary part
//    }
//
//    fftw_execute(p);
//
//    for (int i = 0; i < FFT_SIZE / 2; ++i) {
//        magnitudes[i] = sqrt(out[i][0] * out[i][0] + out[i][1] * out[i][1]);
//    }
//
//    fftw_destroy_plan(p);
//    fftw_free(in);
//    fftw_free(out);
//}
//
//int main() {
//    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Audio Visualizer");
//
//    sf::SoundBuffer buffer;
//    if (!buffer.loadFromFile("My Audio.wav")) {
//        std::cerr << "Error loading audio file" << std::endl;
//        return -1;
//    }
//
//    const sf::Int16* samples = buffer.getSamples();
//    size_t sampleCount = buffer.getSampleCount();
//
//    sf::Sound sound(buffer);
//    sound.play();
//
//    std::vector<double> magnitudes(FFT_SIZE / 2);
//
//    while (window.isOpen()) {
//        sf::Event event;
//        while (window.pollEvent(event)) {
//            if (event.type == sf::Event::Closed)
//                window.close();
//        }
//
//        size_t currentSample = sound.getPlayingOffset().asSeconds() * SAMPLE_RATE;
//        if (currentSample + FFT_SIZE < sampleCount) {
//            std::vector<sf::Int16> sampleChunk(samples + currentSample, samples + currentSample + FFT_SIZE);
//            applyFFT(sampleChunk, magnitudes);
//        }
//
//        window.clear();
//
//        for (size_t i = 0; i < magnitudes.size(); ++i) {
//            float barHeight = magnitudes[i] * 0.01;
//            sf::RectangleShape bar(sf::Vector2f(WINDOW_WIDTH / (float)magnitudes.size(), barHeight));
//            bar.setPosition(i * (WINDOW_WIDTH / (float)magnitudes.size()), WINDOW_HEIGHT - barHeight);
//            bar.setFillColor(sf::Color::Green);
//            window.draw(bar);
//        }
//
//        window.display();
//    }
//
//    return 0;
//}
