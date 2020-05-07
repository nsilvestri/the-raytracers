#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "vec3.h"

vec3 vec3_new(float x, float y, float z) {
    vec3 v;
    v.x = x;
    v.y = y;
    v.z = z;
    return v;
}

float vec3_length(vec3 v) {
    return sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
}

vec3 vec3_scale(vec3 v, float scale) {
    vec3 result;
    result.x = v.x * scale;
    result.y = v.y * scale;
    result.z = v.z * scale;
    return result;
}

vec3 vec3_normalize(vec3 v) {
    // do degenerate case check
    if (vec3_length(v) == 0) {
        return v;
    }

    // scale by 1 / length, which sends length(v) to 1
    return vec3_scale(v, 1.0 / vec3_length(v));
}

vec3 vec3_add(vec3 v1, vec3 v2) {
    vec3 result;
    result.x = v1.x + v2.x;
    result.y = v1.y + v2.y;
    result.z = v1.z + v2.z;
    return result;
}

vec3 vec3_sub(vec3 v1, vec3 v2) {
    // negate v2, store into result, and then add the negation
    return vec3_add(v1, vec3_scale(v2, -1.0));
}

float vec3_dot(vec3 v1, vec3 v2) {
    return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

vec3 vec3_random_in_unit_sphere() {
    vec3 v;
    while (1) {
        // vec3 with components a random length from 0 to 1
        vec3 random_vec3 = vec3_new(drand48(), drand48(), drand48());
        // double it; components random from 0 to 2
        random_vec3 = vec3_scale(random_vec3, 2);
        // this is just a vec3 with all 1 components. Bad name. Whatever.
        vec3 cube_diag = vec3_new(1, 1, 1);
        // we will create a vec3 that lands somewhere in the -1 to +1 cube
        vec3 unit_cube_vec3 = vec3_sub(cube_diag, random_vec3);

        // check if unit_cube_vec3 is longer than 1; AKA, outside of the unit sphere.
        if (vec3_length(unit_cube_vec3) < 1.0) {
            v = unit_cube_vec3;
            break;
        }
    }
    return v;
}

vec3 vec3_gamma_correct(vec3 color, float gamma) {
    vec3 result;
    result.x = pow(color.x, gamma);
    result.y = pow(color.y, gamma);
    result.z = pow(color.z, gamma);
    return result;
}

vec3 vec3_reflect(vec3 v, vec3 normal) {
    // return v - 2 * dot(v, n) * n
    float two_dot_VN = 2 * vec3_dot(v, normal);
    vec3 scaled_normal = vec3_scale(normal, 2 * two_dot_VN);
    return vec3_sub(v, scaled_normal);
}