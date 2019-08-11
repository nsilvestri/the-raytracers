#ifndef _SCENE_H_
#define _SCENE_H_

#include "vec3.h"
#include "ray3.h"
#include "surface.h"

vec3* scene_color(ray3* r, surface** surfaces, int num_surfaces);

/**
 * @brief Returns a random vector with a length of 1.0 or less.
 * 
 * @return vec3* a random vector with a length of 1.0 or less.
 */
vec3* random_in_unit_sphere();

#endif