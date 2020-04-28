#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "scene.h"
#include "vec3.h"
#include "ray3.h"
#include "surface.h"
#include "material.h"

scene scene_new() {
    scene s;
    // manually add surfaces (for now)
    s.num_surfaces = 4;
    material rough_copper = material_metal_new(0.7, vec3_new(1.0, 0.4, 0.05), 0.8);
    material mirror = material_metal_new(0.99, vec3_new(0, 0, 0), 0.0);
    material green_matte = material_lambertian_new(0.5, vec3_new(0.8, 0.8, 0.0));
    material red_matte = material_lambertian_new(0.5, vec3_new(1.0, 0.3, 0.3));
    surface sphere_big = surface_sphere_new(vec3_new(0, -100.5, -1), 100, green_matte);
    surface sphere_red = surface_sphere_new(vec3_new(-1.0, 0, -1), 0.5, red_matte);
    surface sphere_copper = surface_sphere_new(vec3_new(0, -0.1, -1), 0.4, rough_copper);
    surface sphere_mirror = surface_sphere_new(vec3_new(0.75, -0.2, -0.5), 0.3, mirror);
    s.surfaces = malloc(sizeof(surface*) * 4);
    s.surfaces[0] = sphere_big; 
    s.surfaces[1] = sphere_red; 
    s.surfaces[2] = sphere_copper; 
    s.surfaces[3] = sphere_mirror;
    return s;
}

vec3 scene_color(ray3 r, surface* surfaces, int num_surfaces) {
    /* Find the nearest surface which r intersects */

    surface nearest;
    float nearest_t = INFINITY;

    for (int i = 0; i < num_surfaces; i++) {
        surface current_surface = surfaces[i];
        hit_record hit_record = surface_hit(current_surface, r);
        // a miss is -INFINITY, but all t < 0 are behind us
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
        new_ray_color = scene_color(scattered, surfaces, num_surfaces);
    }
    else {
        new_ray_color = nearest.mat.color;
    }
    // attenuate color by albedo
    return vec3_scale(new_ray_color, nearest.mat.albedo);
}
 