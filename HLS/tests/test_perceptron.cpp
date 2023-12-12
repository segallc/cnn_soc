#include <iostream>

#include <perceptron.h>
#include <coeffs.h>

int main(){
    dType img_in[MAX_SIZE] = {0.5};
    dType img_out[MAX_SIZE];

    if (perceptron(img_in, coeffs, img_out)){
        for (int i = 0 ; i < 20 ; i++){
            std::cout << i <<  " : " << img_out[i] << std::endl; 
        }
    }

    return 0;
}