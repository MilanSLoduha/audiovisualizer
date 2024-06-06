#include <fftw3.h>
#include <SFML/Audio.hpp>
#include "main.hpp"
//#include <GLFW/glfw3.h>

#include <iostream>

// convenience macros for the real and imaginary parts
constexpr int REAL = 0;
constexpr int IMAG = 1;
// length of the complex arrays
constexpr int N = 8;

/* Computes the 1-D fast Fourier transform. */
void fft(fftw_complex* in, fftw_complex* out)
{
    // create a DFT plan
    fftw_plan plan = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
    // execute the plan
    fftw_execute(plan);
    // do some cleaning
    fftw_destroy_plan(plan);
    fftw_cleanup();
}

/* Computes the 1-D inverse fast Fourier transform. */
void ifft(fftw_complex* in, fftw_complex* out)
{
    // create an IDFT plan
    fftw_plan plan = fftw_plan_dft_1d(N, in, out, FFTW_BACKWARD, FFTW_ESTIMATE);
    // execute the plan
    fftw_execute(plan);
    // do some cleaning
    fftw_destroy_plan(plan);
    fftw_cleanup();
    // scale the output to obtain the exact inverse
    for (int i = 0; i < N; ++i) {
        out[i][REAL] /= N;
        out[i][IMAG] /= N;
    }
}

/* Displays complex numbers in the form a +/- bi. */
void displayComplex(fftw_complex* y)
{
    for (int i = 0; i < N; ++i) {
        if (y[i][IMAG] < 0) {
            std::cout << y[i][REAL] << " - " << abs(y[i][IMAG]) << "i" << std::endl;
        }
        else {
            std::cout << y[i][REAL] << " + " << y[i][IMAG] << "i" << std::endl;
        }
    }
}

/* Displays the real parts of complex numbers. */
void displayReal(fftw_complex* y)
{
    for (int i = 0; i < N; ++i) {
        std::cout << y[i][REAL] << std::endl;
    }
}

/* Test */
int main()
{
    // input array
    fftw_complex x[N];
    // output array
    fftw_complex y[N];
    // fill the first array with some numbers
    for (int i = 0; i < N; ++i) {
        x[i][REAL] = i + 1.;        // i.e., { 1, 2, 3, 4, 5, 6, 7, 8 }
        x[i][IMAG] = 0;
    }
    // compute the FFT of x and store the results in y
    fft(x, y);
    // display the results
    std::cout << "FFT =\n";
    displayComplex(y);
    // compute the IFFT of y and store the results in x
    ifft(y, x);
    // display the results
    std::cout << "\nIFFT =\n";
    displayReal(x);
	window Window;

    Window.windowRun();
	////////////opengl test ...............................................................................................................
 //////////   glfwwindow* window;

 //////////   /* initialize the library */
 //////////   if (!glfwinit())
 //////////       return -1;

 //////////   /* create a windowed mode window and its opengl context */
 //////////   window = glfwcreatewindow(640, 480, "hello world", null, null);
 //////////   if (!window)
 //////////   {
 //////////       glfwterminate();
 //////////       return -1;
 //////////   }

 //////////   /* make the window's context current */
 //////////   glfwmakecontextcurrent(window);

 //////////   /* loop until the user closes the window */
 //////////   while (!glfwwindowshouldclose(window))
 //////////   {
 //////////       /* render here */
 //////////       glclear(gl_color_buffer_bit);

 //////////       /* swap front and back buffers */
 //////////       glfwswapbuffers(window);

 //////////       /* poll for and process events */
 //////////       glfwpollevents();
 //////////   }

 //////////   glfwterminate();

    return 0;
}