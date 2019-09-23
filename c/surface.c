#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "vec3.h"
#include "ray3.h"
#include "surface.h"
#include "material.h"

surface* surface_sphere_new(vec3* position, float radius, material* m) {
    surface* s = malloc(sizeof(surface));
    if (s == NULL) {
        fprintf(stderr, "Out of memory");
    }
    s->type = SURFACE_SPHERE;
    s->mat = m;
    s->sphere_origin = position;
    s->sphere_radius = radius;
    return s;
}

/**
 * @brief Determine information about the intersection between the given surface
 *        s and a given ray3 r.
 *        The returned pointer is a hit_record populated with the t parameter
 *        for the given ray, such that hit_by_parameter(r, t) returns the point
 *        which r intersects s in xyz space.
 *        If s and r do not intersect, the returned hit_record's t will be
 *        -INFINITY and who knows what its normal vec3 will be.
 * 
 * @param s a pointer to the surface to check intersection
 * @param r a pointer to the ray3 to check intersection
 * @return hit_record* a pointer to a hit_record populated with the appropriate
 *        t and normal vectors.
 */
hit_record* surface_hit(surface* s, ray3* r) {
    if (s->type == SURFACE_SPHERE) {
        vec3* oc = vec3_sub(vec3_new(0, 0, 0), r->origin, s->sphere_origin);
        /* a, b, c are A, B, C of quadratic equation */
        // a = (dir . dir)
        float a = vec3_dot(r->direction, r->direction);
        // b = (dir . (eye - sphere_origin))
        float b = 2 * vec3_dot(oc, r->direction);
        // c = (ray_pos - sphere_center) . (ray_pos - sphere_center) - R^2
        float c = vec3_dot(oc, oc) - (s->sphere_radius * s->sphere_radius);
        // discr = B^2-4AC
        float discriminant = (b * b) - (4 * a * c);

        /* filling hit_record */
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

        // point_of_intersection is self-explanatory
        vec3* point_of_intersection = ray3_point_at_parameter(vec3_new(0, 0, 0), r, t);
        // normal_direction is the vec3 from sphere center to p_o_i
        vec3* normal_direction = vec3_sub(vec3_new(0, 0, 0), point_of_intersection, s->sphere_origin);
        // normalize the normal because why not? Might not be totally necessary
        vec3* normal = vec3_normalize(vec3_new(0, 0, 0),  normal_direction);

        // clean up
        free(oc);
        free(point_of_intersection);
        free(normal_direction);

        return hit_record_new(t, normal);
    }
}

hit_record* hit_record_new(float t, vec3* normal) {
    hit_record* hr = malloc(sizeof(hit_record));
    if (hr == NULL) {
        fprintf(stderr, "Out of memory");
    }
    hr->t = t;
    hr->normal = normal;
    return hr;
}