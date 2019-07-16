#include <stdio.h>

#include "vector3d.h"

int main(int argc, char** argv) {
    vector3d* v = vector3d_make(1, 0, 0);
    printf("v = [%f, %f, %f]\n", v->x, v->y, v->z);
    printf("length = %f\n", vector3d_length(v));
    float dot_result = vector3d_dot(v, vector3d_make(0, 1, 0));
    printf("dot V(0, 1, 0) = %f\n", dot_result);
    return 0;
}
     
