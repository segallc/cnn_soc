#ifndef TYPES_H
#define TYPES_H

#include "ac_fixed.h"
#define  WIDTH 16
#define  I     9

// | <------------ W ----------------> |
// | 0 <-- I --> 0 . 0 <-- W - I --> 0 |
// AC_RND -> Round up number towards infinity
typedef ac_fixed<WIDTH, I, true, AC_RND> dType;
// typedef float dType;

// unsigned 64 bits integer
typedef ac_int<7,false> iType;
// typedef int iType;

#endif
