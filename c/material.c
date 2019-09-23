#include <stdlib.h>
#include <stdio.h>

#include "material.h"
#include "vec3.h"
#include "surface.h"

material* material_lambertian_make(float albedo, vec3* color) {
    material* new_material = malloc(sizeof(material));
    if (new_material == NULL) {
        fprintf(stderr, "out of memory\n");
        exit(1);
    }

    new_material->type = MATERIAL_LAMBERTIAN;
    new_material->albedo = albedo;
    new_material->color = color;

    return new_material;
}

material* material_metal_make(float albedo, vec3* color, float roughness) {
    material* new_material = malloc(sizeof(material));
    if (new_material == NULL) {
        fprintf(stderr, "out of memory\n");
        exit(1);
    }

    new_material->type = MATERIAL_METAL;
    new_material->albedo = albedo;
    new_material->color = color;
    new_material->metal_roughness = roughness;
    return new_material;
}

ray3* material_scatter(material* m, ray3* r, vec3* point_of_intersection, vec3* normal) {
    // new ray always has origin at our point of intersection
    ray3* scattered = ray3_make(point_of_intersection, NULL);
    if (m->type == MATERIAL_METAL) {
        vec3* reflected = vec3_reflect(vec3_make(0, 0, 0), r->direction, normal);
        vec3* roughness_bounce = vec3_scale(vec3_make(0, 0, 0), vec3_random_in_unit_sphere(), m->metal_roughness);
        scattered->direction = vec3_add(vec3_make(0, 0, 0), reflected, roughness_bounce);
        free(reflected);
        free(roughness_bounce);
    }
    else if (m->type == MATERIAL_LAMBERTIAN) {
        // bounce towards a random piont in the unit sphere tangent to the hit point
        vec3* bounce_noise = vec3_random_in_unit_sphere();
        // the direction of this bounce is the normal plus the randomness (noise)
        vec3* bounce_direction = vec3_add(vec3_make(0, 0, 0), normal, bounce_noise);
        // aim for the p_o_i modified by bounce direction
        vec3* target = vec3_add(vec3_make(0, 0, 0), point_of_intersection, bounce_direction);
        // direction of new ray is target position - p_o_i
        vec3* new_ray_direction = vec3_sub(vec3_make(0, 0, 0), target, point_of_intersection);

        // set scattered direction
        scattered->direction = new_ray_direction;
        
        // clean up
        free(bounce_noise);
        free(bounce_direction);
        free(target);
    }
    else {
        fprintf(stderr, "Unknown material type\n");
        exit(1);
    }

    return scattered;
}

int material_should_scatter(material* m) {
    float gen = drand48();
    if (gen <= m->albedo) {
        return 1;
    }
    else {
        return 0;
    }
}


