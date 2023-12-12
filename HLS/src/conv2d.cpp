#include "conv2d.h"

using namespace std;
#pragma hls_design top
int conv2d(
    dType input_fm[MAX_SIZE],
    dType output_fm[MAX_SIZE],
    dType kernel[ROM_SIZE],

    iType size_fm_x,
    iType size_fm_y,
    iType size_fm_z,

    iType size_k_x,
    iType size_k_y,
    iType size_k_z,
    iType nbk,
    // iType bias_nbr, = nbk 
    iType conv_idx
){
    for(int k_idx = 0; k_idx < nbk; k_idx++) {
        // For each kernel layer
        KERZ : for(int kz = 0; kz < size_k_z; kz++) {
            IFMY : for(int y = 0; y < size_fm_y; y++) {
                IFMX : for(int x = 0; x < size_fm_x; x++) {
                    // std::cout << "FMX : " << x << "\nFMY : " << y << std::endl;
                    // accumulateur
                    dType acc = 0;
                    iType X   = 0;
                    iType Y   = 0;
                    // cout << "x : " << x << " y : " << y << endl;
                    KERX : for(int kx = 0; kx < size_k_x; kx++) {
                        KERY : for(int ky = 0; ky < size_k_y; ky++) {
                            X = x - size_k_x/2 + kx;
                            Y = y - size_k_y/2 + ky;
                            if((X >= 0) && (Y >= 0) &&  (X < size_fm_x) && (Y < size_fm_y)) {
                                
                                // std::cout <<  "Idxs : X  : " << X <<  "; Y  : " << Y <<  "; Z  : " << z <<  " === ";
                                // std::cout <<  "Iidx : x  : " << x <<  "; y  : " << y <<  "; z  : " << z <<  " === ";
                                // std::cout <<  "kidx : kx : " << kx << "; ky : " << ky << "; kz : " << kz << " === ";

                                // std::cout <<       "Ridx : " << fm(X, Y, z)                              << " === ";
                                // std::cout <<       "IFM  : " << input_fm[fm(X, Y, z)]                    << " === ";
                                // std::cout <<       "KER  : " << kernel[ki(kx,ky,kz,conv_idx)]            << std::endl; 

                                acc += input_fm[fm(X, Y,kz)]*kernel[ki(kx,ky,kz,k_idx, conv_idx)];

                                // cout << "kx : " <<  kx << " ky : " << ky << " kz : " << kz << " k_idx : " << k_idx << endl;
                                // printf("I:  %.3f K:  %.3f\n", input_fm[fm(X, Y, kz)], kernel[ki(kx,ky,kz,k_idx,conv_idx)]);
                                // printf("X:  %d Y:  %d K: %.3f\n", X, Y, kernel[ki(kx,ky,kz,k_idx,conv_idx)]);
                                // cout << "X:  " << X << " Y:  " << Y << " K:  " <<  kernel[ki(kx,ky,kz,k_idx,conv_idx)] << endl;
                            }
                        }
                    }
                    // cout << "ACC : " << acc << endl;
                    output_fm[fm(x,y,k_idx)] += acc;
                }
                }
        }
        for(int x = 0; x < size_fm_x; x++) {
            for(int y = 0; y < size_fm_y; y++) {
                output_fm[fm(x,y,k_idx)] += kernel[b(k_idx, conv_idx)];

                output_fm[fm(x,y,k_idx)] = (output_fm[fm(x,y,k_idx)] > 0) ? output_fm[fm(x,y,k_idx)] : 0;
            }
        }
    }
    return 1;
}