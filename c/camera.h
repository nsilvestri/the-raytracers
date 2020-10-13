#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "vec3.h"

typedef struct camera {
    vec3 position;
    vec3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
} camera;

#endif