#include <math.h>
#include <stdlib.h>

#include "scene.h"
#include "vec3.h"
#include "ray3.h"
#include "surface.h"

vec3* scene_color(ray3* r, surface** surfaces, int num_surfaces) {
    // Find the nearest surface which r intersects
    surface* nearest;
    float nearest_t = INFINITY;

    for (int i = 0; i < num_surfaces; i++) {
        surface* current_surface = surfaces[i];
        hit_record* hit_record = surface_hit(current_surface, r);
        if (hit_record->t < nearest_t && hit_record->t > 0) {
            nearest_t = hit_record->t;
            nearest = current_surface;
        }
    }

    // no intersection; return sky color by default
    if (nearest_t == INFINITY) {
        vec3* unit_direction = vec3_normalize(r->direction);
        float t = 0.5 * (unit_direction->y + 1.0);
        return vec3_add(
            vec3_scale(vec3_make(1, 1, 1), 1.0 - t),
            vec3_scale(vec3_make(0.5, 0.7, 1.0), t)
        );
    }

    // nearest now contains the nearest surface; calculate the color
    hit_record* hit_record = surface_hit(nearest, r);
    vec3* point_of_intersection = ray3_point_at_parameter(r, hit_record->t);

    // choose a random point in the unit sphere tangent to the hit point
    vec3* target = vec3_add(
        point_of_intersection,
        vec3_add(
            hit_record->normal,
            random_in_unit_sphere()
        )
    );

    ray3* new_ray = ray3_make(
        point_of_intersection,
        vec3_sub(target, point_of_intersection)
    );

    vec3* new_ray_color = scene_color(new_ray, surfaces, num_surfaces);

    // surfaces are 50% reflective
    return vec3_scale(new_ray_color, 0.5);
}
 
vec3* random_in_unit_sphere() {
    vec3* v;
    do {
        v = vec3_sub(
            vec3_scale(vec3_make(drand48(), drand48(), drand48()), 2.0),
            vec3_make(1.0, 1.0, 1.0)
        );
    }
    while (vec3_length(v) > 1.0);
    return v;
}