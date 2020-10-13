#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "material.h"
#include "vec3.h"
#include "surface.h"

material* material_lambertian_new(char* name, float albedo, vec3 color) {
    material* new_material = malloc(sizeof(material));
    new_material->name = malloc(sizeof(char) * 24); // arbitrary 24 char name limit
    new_material->name = strcpy(new_material->name, name);
    new_material->type = MATERIAL_LAMBERTIAN;
    new_material->albedo = albedo;
    new_material->color = color;

    return new_material;
}

material* material_metal_new(char* name, float albedo, vec3 color, float roughness) {
    material* new_material = malloc(sizeof(material));
    new_material->name = malloc(sizeof(char) * 24); // arbitrary 24 char name limit
    new_material->name = strcpy(new_material->name, name);
    new_material->type = MATERIAL_METAL;
    new_material->albedo = albedo;
    new_material->color = color;
    new_material->metal_roughness = roughness;

    return new_material;
}

ray3 material_scatter(material m, ray3 r, vec3 point_of_intersection, vec3 normal) {
    // new ray always has origin at our point of intersection
    vec3 scattered_origin = point_of_intersection;
    vec3 scattered_direction;
    if (m.type == MATERIAL_METAL) {
        vec3 reflected = vec3_reflect(r.direction, normal);
        vec3 roughness_bounce = vec3_scale(vec3_random_in_unit_sphere(), m.metal_roughness);
        scattered_direction = vec3_add(reflected, roughness_bounce);
    }
    else if (m.type == MATERIAL_LAMBERTIAN) {
        // bounce towards a random piont in the unit sphere tangent to the hit point
        vec3 bounce_noise = vec3_random_in_unit_sphere();
        // the direction of this bounce is the normal plus the randomness (noise)
        vec3 bounce_direction = vec3_add(normal, bounce_noise);
        // aim for the p_o_i modified by bounce direction
        vec3 target = vec3_add(point_of_intersection, bounce_direction);
        // direction of new ray is target position - p_o_i
        vec3 new_ray_direction = vec3_sub(target, point_of_intersection);

        // set scattered direction
        scattered_direction = new_ray_direction;
    }
    else {
        fprintf(stderr, "Unknown material type\n");
        exit(1);
    }

    return ray3_new(scattered_origin, scattered_direction);
}

int material_should_scatter(material m) {
    float gen = drand48();
    if (gen <= m.albedo) {
        return 1;
    }
    else {
        return 0;
    }
}


