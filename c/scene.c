#include <math.h>
#include <stdlib.h>

#include "scene.h"
#include "vec3.h"
#include "ray3.h"
#include "surface.h"

vec3* scene_color(ray3* r, surface** surfaces, int num_surfaces) {
    /* Find the nearest surface which r intersects */
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

    /* BASE CASE: no intersection; return sky color by default */

    if (nearest_t == INFINITY) {
        vec3* unit_direction = vec3_make(0, 0, 0);
        unit_direction = vec3_normalize(unit_direction, r->direction);

        // proportion of sky color mixture
        float t = 0.5 * (unit_direction->y + 1.0);

        vec3* sky_color_gradient = vec3_make(1, 1, 1);
        sky_color_gradient = vec3_scale(sky_color_gradient, sky_color_gradient, 1.0 - t);

        vec3* base_sky_color = vec3_make(0.5, 0.7, 1.0);
        base_sky_color = vec3_scale(base_sky_color, base_sky_color, t);

        vec3* sky_color = vec3_make(0, 0 ,0);
        sky_color = vec3_add(sky_color, sky_color_gradient, base_sky_color);
        
        // clean up
        free(unit_direction);
        free(sky_color_gradient);
        free(base_sky_color);

        return sky_color;
    }

    /* nearest now contains the nearest surface; calculate the color */

    hit_record* hit_record = surface_hit(nearest, r);

    // point of intersection is where r intersected the surface in xyz space
    vec3* point_of_intersection = ray3_point_at_parameter(vec3_make(0, 0, 0), r, hit_record->t);

    // bounce towards a random point in the unit sphere tangent to the hit point
    vec3* bounce_random = vec3_random_in_unit_sphere();

    vec3* bounce_direction = vec3_add(vec3_make(0, 0, 0), hit_record->normal, bounce_random);

    vec3* target = vec3_add(vec3_make(0, 0, 0), point_of_intersection, bounce_direction);

    vec3* new_ray_direction = vec3_sub(vec3_make(0, 0, 0), target, point_of_intersection);

    ray3* new_ray = ray3_make(point_of_intersection, new_ray_direction);

    // recursive bouncing color
    vec3* new_ray_color = scene_color(new_ray, surfaces, num_surfaces);

    // surfaces are 50% reflective
    return vec3_scale(new_ray_color, new_ray_color, 0.5);
}
 