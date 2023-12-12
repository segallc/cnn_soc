#include "maxPool.h"
#include <iostream>

using namespace std;

int maxpool(iType x, iType y, iType z, dType img_in[MAX_SIZE], dType img_out[MAX_SIZE]){
    iType cursor_x, cursor_y;
    dType max = 0;
    if ( x == 0 || y == 0 || z == 0 || img_in == NULL || img_out == NULL){
        return 0;
    }
    else {  
        MP_Z: for (int f = 0 ; f < z ; f++){
            MP_Y: for (int l = 1 ; l < y ; l+=2){
                MP_X: for (int c = 1 ; c < x ; c+=2){
                    max = 0;
                    MP_D1: for (int d1 = -1 ; d1 <= 1 ; d1++){
                        MP_D2: for (int d2 = -1 ; d2 <= 1 ; d2++){
                            cursor_x = c + d1;
                            cursor_y = l + d2;
                            if (cursor_x >= 0 && cursor_y >= 0 && cursor_x < x && cursor_y < y ){
                                    // cout << "##MIN" << endl;
                                // cout << cursor_x + cursor_y * MAX_SIZE_X + f*MAX_SIZE_Y*MAX_SIZE_Z << " with " << img_in[cursor_x + cursor_y * MAX_SIZE_X + f*MAX_SIZE_Y*MAX_SIZE_Z] << endl;
                                if (img_in[fm(cursor_x, cursor_y, f)] > max){
                                    max = img_in[fm(cursor_x, cursor_y, f)];
                                }
                            }
                        }
                    }
                     // cout << "written   : " << max << "  here  " << f*MAX_SIZE_X*MAX_SIZE_Y+c/2+(l/2)*MAX_SIZE_X <<  endl;
                    img_out[f*MAX_SIZE_X*MAX_SIZE_Y+c/2+(l/2)*MAX_SIZE_X] = max;
                }
            }
        }
        return 1;
    }
}
