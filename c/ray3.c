#include <stdio.h>
#include <stdlib.h>
#include "ray3.h"

ray3* ray3_new(vec3* origin, vec3* direction) {
    ray3* r = malloc(sizeof(ray3));
    if (r == NULL) {
        fprintf(stderr, "Out of memory\n");
        exit(1);
    }
    r->origin = origin;
    r->direction = direction;
    return r;
}

vec3* ray3_point_at_parameter(vec3* result, ray3* r, float t) {
    vec3* scaled_direction = vec3_scale(vec3_new(0, 0, 0), r->direction, t);
    result = vec3_add(result, r->origin, scaled_direction);
    free(scaled_direction);
    return result;
}