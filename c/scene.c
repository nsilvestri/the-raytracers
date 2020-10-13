#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "scene.h"
#include "vec3.h"
#include "ray3.h"
#include "surface.h"
#include "material.h"

scene scene_new() {
    scene s;
    s.num_surfaces = 0;
    s.internal_surface_array_size = 8;
    s.surfaces = malloc(sizeof(surface) * s.internal_surface_array_size);
    return s;
}

vec3 scene_color(ray3 r, scene s) {
    /* Find the nearest surface which r intersects */

    surface nearest;
    float nearest_t = INFINITY;

    for (int i = 0; i < s.num_surfaces; i++) {
        surface current_surface = s.surfaces[i];
        hit_record hit_record = surface_hit(current_surface, r);
        // a miss is -INFINITY, but all t < 0 are behind the camera
        if (hit_record.t < nearest_t && hit_record.t > 0) {
            nearest_t = hit_record.t;
            nearest = current_surface;
        }
    }

    /* BASE CASE: no intersection; return sky color by default */

    if (nearest_t == INFINITY) {
        // normalize direction of ray so all values of y will be consistent
        vec3 unit_direction = vec3_normalize(r.direction);

        // proportion of sky color mixture based on y component (up-ness)
        float t = 0.5 * (unit_direction.y + 1.0);

        // base color of sky
        vec3 base_sky_color = vec3_new(0.5, 0.7, 1.0);
        base_sky_color = vec3_scale(base_sky_color, t);

        // what color the sky fades into, going down
        vec3 sky_color_gradient = vec3_new(1, 1, 1);
        sky_color_gradient = vec3_scale(sky_color_gradient, 1.0 - t);

        // add base_sky_color and sky_color_gradient
        return vec3_add(base_sky_color, sky_color_gradient);
    }

    /* nearest now contains the nearest surface; calculate the color */

    hit_record hit_record = surface_hit(nearest, r);

    // recursive bouncing color
    vec3 new_ray_color;
    if (material_should_scatter(nearest.mat)) {
        // point of intersection is where r intersected the surface in xyz space
        vec3 point_of_intersection = ray3_point_at_parameter(r, hit_record.t);
        ray3 scattered = material_scatter(nearest.mat, r, point_of_intersection, hit_record.normal);
        new_ray_color = scene_color(scattered, s);
    }
    else {
        new_ray_color = nearest.mat.color;
    }
    // attenuate color by albedo
    return vec3_scale(new_ray_color, nearest.mat.albedo);
}

void scene_add_surface(scene* scene, surface surf) {
    // if there is no space for the new surface, make the array bigger
    if (scene->num_surfaces >= scene->internal_surface_array_size) {
        surface* new_surface_array = malloc(sizeof(scene->surfaces) * scene->internal_surface_array_size * 2);
        memcpy(new_surface_array, scene->surfaces, sizeof(scene->surfaces) * scene->internal_surface_array_size);
        scene->internal_surface_array_size = scene->internal_surface_array_size * 2;
        scene->surfaces = new_surface_array;
    }

    // add the new surface
    scene->surfaces[scene->num_surfaces] = surf;
    scene->num_surfaces++;
}
 