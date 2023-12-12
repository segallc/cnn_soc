#include "maxPool.h"
#include <perceptron.h>
#include <reshape.h>
#include <conv2d.h>
#include "img.h"
#include "coeffs.h"
#include "meta.h"

int main(){
    dType output_fm_conv1[MAX_SIZE]      = {0};
    dType output_fm_maxpool1[MAX_SIZE]   = {0};

    dType output_fm_conv2[MAX_SIZE]      = {0};
    dType output_fm_maxpool2[MAX_SIZE]   = {0};

    dType output_fm_conv3[MAX_SIZE]      = {0};
    dType output_fm_maxpool3[MAX_SIZE]   = {0};

    dType output_fm_reshape[MAX_SIZE]    = {0};
    dType output_fm_perceptron[MAX_SIZE] = {0};

    if (!conv2d(img, output_fm_conv1, coeffs, 24, 24, 3, 3, 3, 3, 64, 0)){
        return EXIT_FAILURE;
    }


    if (!maxpool(24, 24, 64, output_fm_conv1, output_fm_maxpool1)){
        return EXIT_FAILURE;
    }


    if (!conv2d(output_fm_maxpool1, output_fm_conv2, coeffs, 12, 12, 64, 3, 3, 64, 32, 1)){
        return EXIT_FAILURE;
    }

    if (!maxpool(12, 12, 32, output_fm_conv2, output_fm_maxpool2)){
        return EXIT_FAILURE;
    }

    if (!conv2d(output_fm_maxpool2, output_fm_conv3, coeffs, 6, 6, 32, 3, 3, 32, 20, 2)){
        return EXIT_FAILURE;
    }

    if (!maxpool(6, 6, 20, output_fm_conv3, output_fm_maxpool3)){
        return EXIT_FAILURE;
    }

    if (!reshape(3, 3, 20, output_fm_maxpool3, output_fm_reshape)){
        return EXIT_FAILURE;
    }

    if (!perceptron(output_fm_reshape, coeffs, output_fm_perceptron)){
        return EXIT_FAILURE;
    }

    dType max = output_fm_perceptron[0];
    int i_max = 0;
    for (int i = 0 ; i < PERCEP_OUT ; i++){
        // printf("%.3f\n", output_fm_perceptron[i]);
        if ( output_fm_perceptron[i] > max ){
            max = output_fm_perceptron[i];
            i_max = i;
        }
    }

    cout << i_max << "=";

    return i_max;
}