#include "conv2d.h"
#include "img.h"
#include "sizes.h"
#include "types.h"
#include "coeffs.h"

int main(int argc, char const *argv[])
{
    dType output_fm_conv1[MAX_SIZE] = {0};

    conv2d(img, output_fm_conv1, coeffs, 24, 24, 3, 3, 3, 3, 64, 0);

    return 0;
}
