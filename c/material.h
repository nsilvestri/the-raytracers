#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "vec3.h"
#include "ray3.h"

typedef enum {
    MATERIAL_LAMBERTIAN,
    MATERIAL_METAL
} material_type;

typedef struct {
    char* name;
    material_type type;
    float albedo;
    vec3 color;

    float metal_roughness;
} material;

material* material_lambertian_new(char* name, float albedo, vec3 color);
material* material_metal_new(char* name, float albedo, vec3 color, float roughness);

ray3 material_scatter(material m, ray3 r, vec3 point_of_intersection, vec3 normal);

int material_should_scatter(material m);

#endif