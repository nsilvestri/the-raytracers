#ifndef _RAY3_H_
#define _RAY3_H_

#include "vec3.h"

typedef struct ray3 {
    vec3* origin;
    vec3* direction;
} ray3;

ray3* ray3_make(vec3* origin, vec3* direction);

#endif