#include "maxPool.h"
#include "types.h"

using namespace std;


int main(){
    int x = 10;
    int y = 10;
    int z = 3;

    dType img_in[MAX_SIZE];
    dType img_out[MAX_SIZE];


    for (int i = 0 ; i < MAX_SIZE ; i++){
        img_in[i] = i;
    }
    for (int i = 0 ; i < z ; i++){
        cout << endl;
        cout << endl;
        for (int j = 0 ; j < y ; j++){
            cout << endl;
            for (int k = 0 ; k < x ; k++){
                cout << img_in[k+j*MAX_SIZE_X+i*MAX_SIZE_X*MAX_SIZE_Y] << "   ";
            }
        }
    }
    if (maxpool(x, y, z, img_in, img_out)){
        std::cout << "BRAVO" << std::endl;
    }  

    for (int i = 0 ; i < z ; i++){
        cout << endl;
        cout << endl;
        for (int j = 0 ; j < y/2 ; j++){
            cout << endl;
            for (int k = 0 ; k < x/2 ; k++){
                cout << img_out[k+j*MAX_SIZE_X+i*MAX_SIZE_X*MAX_SIZE_Y] << "   ";
            }
        }
    }
    return 0;
}
