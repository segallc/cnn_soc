#ifndef _RESHAPE_H_
#define _RESHAPE_H_

#include "types.h"
#include "sizes.h"

int reshape(int x, int y, int z, dType img_in[MAX_SIZE], dType img_out[RESHAPE_OUT]);
 
#endif