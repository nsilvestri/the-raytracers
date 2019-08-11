#include <math.h>

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

    // no intersection; return black color by default
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
    vec3* color_sample;

    vec3* point_of_intersection = ray3_point_at_parameter(r, hit_record->t);
    vec3* light = vec3_make(1, 1, 1);
    ray3* light_direction = ray3_make(point_of_intersection,
                                        vec3_sub(light, point_of_intersection));

    float lambertian_max = fmax(0,
                                vec3_dot(
                                    vec3_normalize(hit_record->normal),
                                    vec3_normalize(light_direction->direction)
                                ));

    return vec3_make(
                     fabs(lambertian_max),
                     fabs(lambertian_max),
                     fabs(lambertian_max)
                    );
}
 