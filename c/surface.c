#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "vec3.h"
#include "ray3.h"
#include "surface.h"

surface* surface_sphere_make(vec3* position, float radius) {
    surface* s = malloc(sizeof(surface));
    if (s == NULL) {
        fprintf(stderr, "Out of memory");
    }
    s->type = SURFACE_SPHERE;
    s->sphere_origin = position;
    s->sphere_radius = radius;
    return s;
}

hit_record* surface_hit(surface* s, ray3* r) {
    if (s->type == SURFACE_SPHERE) {
        // a, b, c are A, B, C of quadratic equation
        vec3* oc = vec3_make(0, 0, 0);
        oc = vec3_sub(oc, r->origin, s->sphere_origin);
        // a = (dir . dir)
        float a = vec3_dot(r->direction, r->direction);
        // b = (dir . (eye - sphere_origin))
        float b = 2 * vec3_dot(oc, r->direction);
        // c = (ray_pos - sphere_center) . (ray_pos - sphere_center) - R^2
        float c = vec3_dot(oc, oc) - (s->sphere_radius * s->sphere_radius);
        // discr = B^2-4AC
        float discriminant = (b * b) - (4 * a * c);

        // filling hit_record
        float t;
        if (discriminant < 0) {
            t = -INFINITY;
        }
        else {
            // there are two roots; we need the closer (smaller) one
            float tMinus = (-b - sqrt(discriminant)) / (2.0 * a);
            float tPlus = (-b + sqrt(discriminant)) / (2.0 * a);
            t = fmin(tPlus, tMinus);
        }

        vec3* point_of_intersection = vec3_make(0, 0, 0);
        point_of_intersection = ray3_point_at_parameter(point_of_intersection, r, t);

        vec3* normal_direction = vec3_make(0, 0, 0);
        normal_direction = vec3_sub(normal_direction, point_of_intersection, s->sphere_origin);

        vec3* normal = vec3_make(0, 0, 0);
        normal = vec3_normalize(normal,  normal_direction);

        return hit_record_make(t, normal);

        // clean up
        free(oc);
        free(point_of_intersection);
        free(normal_direction);
    }
}

hit_record* hit_record_make(float t, vec3* normal) {
    hit_record* hr = malloc(sizeof(hit_record));
    if (hr == NULL) {
        fprintf(stderr, "Out of memory");
    }
    hr->t = t;
    hr->normal = normal;
    return hr;
}