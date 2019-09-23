#include <stdio.h>
#include <stdlib.h>
#include "ray3.h"

ray3 ray3_new(vec3 origin, vec3 direction) {
    ray3 r;
    r.origin = origin;
    r.direction = direction;
    return r;
}

vec3 ray3_point_at_parameter(ray3 r, float t) {
    vec3 scaled_direction = vec3_scale(r.direction, t);
    return vec3_add(r.origin, scaled_direction);
}