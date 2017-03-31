#ifndef fftw_Convolution_convolution_h
#define fftw_Convolution_convolution_h
#include <fftw3.h>
#include <complex>

typedef std::complex<double> dcomplex;
void fourier(const int N, dcomplex* gw, dcomplex* gt);
void ifourier(const int N, dcomplex* gw, dcomplex* gt);
void convolution(const int N, const double W, dcomplex* gw, dcomplex* fw, dcomplex* hw);

#endif
