#include "reshape.h"
#include "iostream"

using namespace std;

int main(){
    dType img_in[MAX_SIZE];
    dType img_out[MAX_SIZE];

    for (int i = 0 ; i < MAX_SIZE ; i++){
        img_in[i] = i;
    }
    for (int i = 0 ; i < 20 ; i++){
        cout << endl;
        cout << endl;
        for (int j = 0 ; j < 3 ; j++){
            cout << endl;
            for (int k = 0 ; k < 3 ; k++){
                cout << img_in[k+j*MAX_SIZE_X+i*MAX_SIZE_X*MAX_SIZE_Y] << " ";
            }
        }
    }
    if (reshape(3, 3, 20, img_in, img_out)){
        std::cout << "BRAVO" << std::endl;
    }

    for (int i = 0 ; i < PERCEP_IN ; i++){
        cout << img_out[i] << " ";
    }
    return 0;
}