#ifndef _SCENE_H_
#define _SCENE_H_

#include "vec3.h"
#include "ray3.h"
#include "surface.h"

typedef struct scene {
    surface* surfaces;
    int num_surfaces;
} scene;

scene scene_new();

scene scene_read_file(char* filepath);

vec3 scene_color(ray3 r, surface* surfaces, int num_surfaces);

#endif