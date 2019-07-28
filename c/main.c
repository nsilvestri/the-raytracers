#include <stdio.h>

#include "vec3.h"

int main(int argc, char** argv) {
    vec3* v = vec3_make(1, 0, 0);
    printf("v = [%f, %f, %f]\n", v->x, v->y, v->z);
    printf("length = %f\n", vec3_length(v));
    float dot_result = vec3_dot(v, vec3_make(0, 1, 0));
    printf("dot V(0, 1, 0) = %f\n", dot_result);
    return 0;
}
     
