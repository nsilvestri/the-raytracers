#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "vec3.h"

vec3* vec3_make(float x, float y, float z) {
    vec3* v = malloc(sizeof(vec3));
    if (v == NULL) {
        fprintf(stderr, "out of memory\n"); 
        exit(1);
    }
    v->x = x;
    v->y = y;
    v->z = z;
    return v;
}

float vec3_length(vec3* v) {
    return sqrt(pow(v->x, 2) + pow(v->y, 2) + pow(v->z, 2));
}

float vec3_dot(vec3* v1, vec3* v2) {
    return (v1->x * v2->x) + (v1->y * v2->y) + (v1->z * v2->z);
}
