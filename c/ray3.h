#ifndef _RAY3_H_
#define _RAY3_H_

#include "vec3.h"

typedef struct ray3 {
    vec3* origin;
    vec3* direction;
} ray3;

ray3* ray3_make(vec3* origin, vec3* direction);

/**
 * Calculate a point along r such that the point is the end of the vector
 * originating from r->origin pointing towards r->direction and scaled by t. * 
 * @param r ray3* the ray to use for origin and direction.
 * @param t float the scalar for the ray
 * 
 * @return vec3* a vec3* representing some point along r, specified by t.
 */
vec3* ray3_point_at_parameter(ray3* r, float t);

#endif