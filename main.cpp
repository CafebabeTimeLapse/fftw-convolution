#include <iostream>
#include "convolution.h"
#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
#define pi M_PI

inline double func(double w){
    return 1/pi/(w*w+1);
}

std::string int2string(int n){
   std::stringstream ss;
   ss << n;
   return ss.str();
}

int main(int argc, char** argv){
    int N,i;
    double a,b,W,w;
    std::string FuncName,FileName;
    dcomplex *fw, *gw, *nw, *ew;
    std::ofstream ofs;
    
    //////////////////////////////////////////
    // parameters
    W=10; // width
    N = 1000; // # of mesh
    a = -W/2; // w_min
    b = +W/2;  // w_max
    FuncName = "Symmetric"; // function type
    FileName = "graph-"
        +FuncName
        +"-width_"+int2string(int(round(W)))
        +".txt"; // export file
    //////////////////////////////////////////
    

    fw = new dcomplex [N]; // operand
    gw = new dcomplex [N]; // operand
    nw = new dcomplex [N]; // numerical convolution
    ew = new dcomplex [N]; // exact convolution

    
    // generate operand functions
    if(FuncName=="Asymmetric"){
        for(i=0;i<N;i++){
            w=a+(b-a)*i/N;
            fw[i]=func(w-8);
            gw[i]=func(w+2);
            ew[i]=.5*func((w-6)/2);
        }
    }else{
        for(i=0;i<N;i++){
            w=a+(b-a)*i/N;
            fw[i]=func(w-2);
            gw[i]=func(w+2);
            ew[i]=.5*func(w/2);
        }
    }
    
    // calculate convolution
    convolution(N,W,fw,gw,nw);
    
    // export
    ofs.open(FileName.c_str());
    ofs.setf(std::ios::scientific);
    ofs << "# \"w\" \"numerical(real, imag)\" \"exact(real, imag)\"\n";
    for(i=0;i<N;i++){
        w=a+(b-a)*i/N;
        ofs << w << " "
        << nw[i].real() << " " << nw[i].imag() << " "
        << ew[i].real() << " " << ew[i].imag() << "\n";
    }
    ofs.close();
    
    delete [] fw;
    delete [] gw;
    delete [] nw;
    delete [] ew;
    
    return 0;
}
