#ifndef CONV2D_H_
#define CONV2D_H_

#include "types.h"
#include "sizes.h"
#include <iostream>

using namespace std;
// #pragma hls_design top
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
);

#endif