#include <iostream>
#include "convolution.h"


void fourier(const int N, dcomplex* fw, dcomplex* ft){
    fftw_plan p;
    p = fftw_plan_dft_1d(N, reinterpret_cast<fftw_complex*>(fw), reinterpret_cast<fftw_complex*>(ft), FFTW_FORWARD, FFTW_ESTIMATE);
    fftw_execute(p);
    fftw_destroy_plan(p);
}

void ifourier(const int N, dcomplex* ft, dcomplex* fw){
    fftw_plan p;
    p = fftw_plan_dft_1d(N, reinterpret_cast<fftw_complex*>(ft), reinterpret_cast<fftw_complex*>(fw), FFTW_BACKWARD, FFTW_ESTIMATE);
    fftw_execute(p);
    fftw_destroy_plan(p);
}

void convolution(const int N, const double W, dcomplex* fw, dcomplex* gw, dcomplex* hw){
    dcomplex *ft, *gt;
    dcomplex phase;
    
    ft = new dcomplex [N];
    gt = new dcomplex [N];

    fourier(N, fw, ft);
    fourier(N, gw, gt);
    
    phase=-1;
     /* "phase" is necessary for [-W/2,W/2] frequency regime, not for [0,W]. */ 
    for(int t=0;t<N;t++){
        phase*=-1;
        hw[t] = ft[t]*gt[t]*(W/N/N)*phase;
    }
    
    ifourier(N, hw, hw);
    
    delete [] ft;
    delete [] gt;
}