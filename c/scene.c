#include <math.h>
#include <stdlib.h>

#include "scene.h"
#include "vec3.h"
#include "ray3.h"
#include "surface.h"
#include "material.h"

vec3* scene_color(ray3* r, surface** surfaces, int num_surfaces) {
    /* Find the nearest surface which r intersects */

    surface* nearest;
    float nearest_t = INFINITY;

    for (int i = 0; i < num_surfaces; i++) {
        surface* current_surface = surfaces[i];
        hit_record* hit_record = surface_hit(current_surface, r);
        // a miss is -INFINITY, but all t < 0 are behind us
        if (hit_record->t < nearest_t && hit_record->t > 0) {
            nearest_t = hit_record->t;
            nearest = current_surface;
        }

        // clean up on this loop
        free(hit_record->normal);
        free(hit_record);
    }

    /* BASE CASE: no intersection; return sky color by default */

    if (nearest_t == INFINITY) {
        // normalize direction of ray so all values of y will be consistent
        vec3* unit_direction = vec3_normalize(vec3_make(0, 0, 0), r->direction);

        // proportion of sky color mixture based on y component (up-ness)
        float t = 0.5 * (unit_direction->y + 1.0);

        // base color of sky
        vec3* base_sky_color = vec3_make(0.5, 0.7, 1.0);
        base_sky_color = vec3_scale(base_sky_color, base_sky_color, t);

        // what color the sky fades into, going down
        vec3* sky_color_gradient = vec3_make(1, 1, 1);
        sky_color_gradient = vec3_scale(sky_color_gradient, sky_color_gradient, 1.0 - t);

        // add base_sky_color and sky_color_gradient
        vec3* sky_color = vec3_add(vec3_make(0, 0, 0), base_sky_color, sky_color_gradient);
        
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
    vec3* bounce_noise = vec3_random_in_unit_sphere();

    // the direction of this bounce is the normal plus the randomness (noise)
    vec3* bounce_direction = vec3_add(vec3_make(0, 0, 0), hit_record->normal, bounce_noise);

    // the next spot we aim for (target) is the p_o_i modified by our bounce direction
    vec3* target = vec3_add(vec3_make(0, 0, 0), point_of_intersection, bounce_direction);

    // the direction of the new ray is the target position - p_o_i
    vec3* new_ray_direction = vec3_sub(vec3_make(0, 0, 0), target, point_of_intersection);

    // create the new ray cenetered on our p_o_i pointing in our new direction
    ray3* new_ray = ray3_make(point_of_intersection, new_ray_direction);

    // recursive bouncing color
    vec3* new_ray_color;
    if (material_should_scatter(nearest->material)) {
        ray3* scattered = material_scatter(nearest->material, r, point_of_intersection, hit_record->normal);
        new_ray_color = scene_color(scattered, surfaces, num_surfaces);
    }
    else {
        new_ray_color = nearest->material->color;
    }
    new_ray_color = scene_color(new_ray, surfaces, num_surfaces);

    // clean up
    free(hit_record->normal);
    free(hit_record);

    free(point_of_intersection);
    free(bounce_noise);
    free(bounce_direction);
    free(target);
    free(new_ray_direction);
    free(new_ray);

    // attenuate color by albedo
    return vec3_scale(new_ray_color, new_ray_color, nearest->material->albedo);
}
 