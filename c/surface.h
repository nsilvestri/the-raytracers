#ifndef _SURFACE_H_
#define _SURFACE_H_

#include "vec3.h"
#include "ray3.h"
#include "material.h"
#include "hitrecord.h"

typedef enum {
    SURFACE_SPHERE,
    SURFACE_PLANE
} surface_type;

typedef struct surface {
    // fields for all surfaces
    surface_type type;
    material mat;

    // sphere specific fields
    vec3 sphere_origin;
    float sphere_radius;
} surface;

surface surface_sphere_new(vec3 position, float radius, material m);
hit_record surface_hit(surface s, ray3 r);

#endif