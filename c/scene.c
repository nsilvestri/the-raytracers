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
        return vec3_make(0, 0, 0);
    }

    // nearest now contains the nearest surface; calculate the color
    hit_record* hit_record = surface_hit(nearest, r);
    vec3* color_sample;
    if (hit_record->t > 0) {
        float r = fabs(hit_record->normal->x);
        float g = fabs(hit_record->normal->y);
        float b = fabs(hit_record->normal->z);
        color_sample = vec3_make(r, g, b);
    }
    else {
        color_sample = vec3_make(0, 0, 0);
    }
}
 