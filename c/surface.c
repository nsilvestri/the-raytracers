#include <stdlib.h>

#include "vec3.h"
#include "ray3.h"
#include "surface.h"

surface* surface_sphere_make(vec3* position, float radius) {
    surface* s = malloc(sizeof(surface));
    s->type = SURFACE_SPHERE;
    s->sphere_origin = position;
    s->sphere_radius = radius;
    return s;
}

vec3* surface_intersect(surface* s, ray3* r) {
    if (s->type == SURFACE_SPHERE) {
        // a, b, c are A, B, C of quadratic equation
        vec3* oc = vec3_sub(r->origin, s->sphere_origin);
        // a = (dir . dir)
        float a = vec3_dot(r->direction, r->direction);
        // b = (dir . (eye - sphere_origin))
        float b = 2 * vec3_dot(oc, r->direction);
        // c = (ray_pos - sphere_center) . (ray_pos - sphere_center) - R^2
        float c = vec3_dot(oc, oc) - (s->sphere_radius * s->sphere_radius);
        // discr = B^2-4AC
        float discriminant = (b * b) - (4 * a * c);

        if (discriminant < 0) {
            return rgb_make(0, 0, 0);
        }

        return rgb_make(1, 0, 0);
    }
}