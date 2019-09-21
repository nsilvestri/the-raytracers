#include <stdlib.h>
#include <stdio.h>

#include "material.h"
#include "vec3.h"
#include "surface.h"

material* material_lambertian_make(float albedo, vec3* color) {
    material* new_material = malloc(sizeof(material));

    new_material->type = MATERIAL_LAMBERTIAN;
    new_material->albedo = albedo;
    new_material->color = color;

    return new_material;
}

material* material_metal_make(float albedo, vec3* color, float roughness) {
    material* new_material = malloc(sizeof(material));

    new_material->type = MATERIAL_METAL;
    new_material->albedo = albedo;
    new_material->color = color;
    new_material->metal_roughness = roughness;
    return new_material;
}

ray3* material_scatter(material* m, ray3* r, vec3* point_of_intersection, vec3* normal) {
    ray3* scattered = ray3_make(point_of_intersection, NULL);
    if (m->type == MATERIAL_METAL) {
            vec3* reflected = vec3_reflect(vec3_make(0, 0, 0), r->direction, normal);
            vec3* roughness_bounce = vec3_scale(vec3_make(0, 0, 0), vec3_random_in_unit_sphere(), m->metal_roughness);
            scattered->direction = vec3_add(vec3_make(0, 0, 0), reflected, roughness_bounce);
            free(reflected);
            free(roughness_bounce);
    }
    else {
        fprintf(stderr, "Unknown material type\n");
        exit(1);
    }

    return scattered;
}

int material_should_scatter(material* m) {
    return drand48() <= m->albedo;
}


