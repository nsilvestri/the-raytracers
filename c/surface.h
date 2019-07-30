#ifndef _SURFACE_H_
#define _SURFACE_H_

#include "vec3.h"
#include "ray3.h"

typedef enum {
    SURFACE_SPHERE,
    SURFACE_PLANE
} surface_type;

typedef struct {
    surface_type type;

    vec3* sphere_origin;
    float sphere_radius;
} surface;

surface* surface_sphere_make(vec3* position, float radius);
vec3* surface_intersect(surface* s, ray3* r);

#endif