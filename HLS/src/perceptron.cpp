#include "perceptron.h"
#include <iostream>

using namespace std;
// #pragma hls_design top
int perceptron(dType img_in[MAX_SIZE], dType kernels[ROM_SIZE], dType img_out[MAX_SIZE]){
    int cursor = 110784;
    PCLASS: for (int i = 0; i < PERCEP_OUT ; i++){
        img_out[i] = 0;
        PKER: for (int j = 0 ; j < PERCEP_IN ; j++){
            // cout << img_in[j] << endl;
            cursor = 110784 + i + j*10;
            img_out[i] += img_in[j] * kernels[cursor];
        }
    }
    cursor = ROM_SIZE - 10;
    PBIAS: for (int i = 0 ; i < PERCEP_OUT ; i++){
        img_out[i] += kernels[cursor];
        cursor++;
    }
    return 1;
}
