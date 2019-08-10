#ifndef _SCENE_H_
#define _SCENE_H_

#include "vec3.h"
#include "ray3.h"
#include "surface.h"

vec3* scene_color(ray3* r, surface** surfaces, int num_surfaces);

#endif