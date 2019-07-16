#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "vector3d.h"

vector3d* vector3d_make(float x, float y, float z) {
    vector3d* v = malloc(sizeof(vector3d));
    if (v == NULL) {
        fprintf(stderr, "out of memory\n"); 
        exit(1);
    }
    v->x = x;
    v->y = y;
    v->z = z;
    return v;
}

float vector3d_length(vector3d* v) {
    return sqrt(pow(v->x, 2) + pow(v->y, 2) + pow(v->z, 2));
}

float vector3d_dot(vector3d* v1, vector3d* v2) {
    return (v1->x * v2->x) + (v1->y * v2->y) + (v1->z * v2->z);
}
