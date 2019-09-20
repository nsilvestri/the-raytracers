#ifndef _SURFACE_H_
#define _SURFACE_H_

#include "vec3.h"
#include "ray3.h"
#include "material.h"

typedef enum {
    SURFACE_SPHERE,
    SURFACE_PLANE
} surface_type;

typedef struct {
    surface_type type;
    material* material;

    vec3* sphere_origin;
    float sphere_radius;
} surface;

typedef struct hit_record {
    float t;
    vec3* normal;
} hit_record;

surface* surface_sphere_make(vec3* position, float radius, material* m);
hit_record* surface_hit(surface* s, ray3* r);

hit_record* hit_record_make(float t, vec3* normal);

#endif