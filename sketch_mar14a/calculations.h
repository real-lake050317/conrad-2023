#include <math.h>
#include "variables.h"

#ifndef calculations
#define calculations

int topServoAngle (int x, int y, int z) {
    if (y >= 0) {
        return (int)(180.0*atanf((float)(y)/x)/CONST_PI);
    }
    return (int)(180.0*atanf((float)(y)/x)/CONST_PI) + 180;
};

int bottomServoAngle (int x, int y, int z) {
    return (int)(180.0*acosf((float)(z)/sqrt(x*x + y*y + z*z))/CONST_PI);
};

#endif