#include "conv2d.h"
#include <stdint.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#define IMG_SIZE_X 24
#define IMG_SIZE_Y 24
#define IMG_SIZE_Z 1
#define IMG_SIZE   IMG_SIZE_X*IMG_SIZE_Y

#define K_X        3
#define K_Y        3
#define K_Z        1
#define NBK        1

int main() {

    char  img_path[] = "../data/test.pgm";
    dType   img_data[MAX_SIZE];
    // read image
    ifstream img_file;
    img_file.open(img_path);
    dType v = 0;
    int   i = 0;
    if(!img_file.is_open()) {
        cerr << "Error opening the image file." << endl;
        exit(1);
    }
    string img_type;
    int    img_sx;
    int    img_sy;
    int    img_max;
    img_file >> img_type;
    if(img_type != "P2") {
        cout << "Wrong image type." << endl << "Must be P2" << endl;
        exit(2);
    }
    img_file >> img_sx;
    img_file >> img_sy;
    img_file >> img_max;

    cout << "Type : " << img_type << endl << "Size x : " << img_sx << endl;
    cout << "Sixe y :" << img_sx << endl << "Max : " << img_max << endl;

    while(img_file >> v) {
        img_data[i] = v;
        i++;
    }
    img_file.close();

    // kernel
    dType kernel_blur[] = {1/9., 1/9., 1/9., 1/9., 1/9., 1/9., 1/9., 1/9., 1/9.};
    dType kernel_id[] = {0, 0, 0, 0, 1, 0, 0, 0, 0};
    dType kernel_sat[] = {1, 1, 1, 1, 1, 1, 1, 1, 1};

    // cout << "(";
    // for(int i = 0; i < 9; i++) {
    //     if(i%3==0 && i != 0) cout << " )" << endl << "(";
    //     cout << " " << kernel_blur[i];
    // }
    // cout << " )" << endl;
    
    // output img
    dType output_img[IMG_SIZE];

    // convolution
    conv2d(img_data, output_img, kernel_blur, IMG_SIZE_X, IMG_SIZE_Y, IMG_SIZE_Z, K_X, K_Y, K_Z, NBK, 0);

    ofstream o_img;
    o_img.open("conv2d_test_out.pgm");
    o_img << "P2" << endl << "24 24" << endl << 255;
    for(int i = 0; i < IMG_SIZE; i++) {
        if(i % 24 == 0) o_img << endl;
        o_img << (int) output_img[i] << " ";
    }
    o_img.close();

    return 0;
}