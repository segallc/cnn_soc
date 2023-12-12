#ifndef _TOP_CNN_H_
#define _TOP_CNN_H_

#include "maxPool.h"
#include "perceptron.h"
#include "reshape.h"
#include "types.h"
#include "sizes.h"
#include "conv2d.h"
#include "img.h"
#include "coeffs.h"

void top_cnn(dType img_in[MAX_SIZE]);

#endif // _TOP_CNN_H_
