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

vec3* vec3_scale(vec3* result, vec3* v, float scale) {
    result->x = v->x * scale;
    result->y = v->y * scale;
    result->z = v->z * scale;
    return result;
}

vec3* vec3_normalize(vec3* result, vec3* v) {
    // do degenerate case check
    float length = vec3_length(v);
    if (length == 0) {
        result = vec3_make(0, 0, 0);
        return result;
    }

    // scale by 1 / length, which sends length(v) to 1
    return vec3_scale(result, v, 1.0 / length);
}

vec3* vec3_add(vec3* result, vec3* v1, vec3* v2) {
    result->x = v1->x + v2->x;
    result->y = v1->y + v2->y;
    result->z = v1->z + v2->z;
    return result;
}

vec3* vec3_sub(vec3* result, vec3* v1, vec3* v2) {
    // negate v2, store into result, and then add the negation
    return vec3_add(result, v1, vec3_scale(result, v2, -1.0));
}

float vec3_dot(vec3* v1, vec3* v2) {
    return (v1->x * v2->x) + (v1->y * v2->y) + (v1->z * v2->z);
}

vec3* vec3_random_in_unit_sphere() {
    vec3* v = NULL;
    while (1) {
        vec3* random_vec3 = vec3_make(drand48(), drand48(), drand48());
        random_vec3 = vec3_scale(random_vec3, random_vec3, 2);
        random_vec3 = vec3_sub(random_vec3, vec3_make(1, 1, 1), random_vec3);

        if (vec3_length(random_vec3) > 1.0) {
            v = random_vec3;
            break;
        }
        free(random_vec3);
    }
    return v;
}