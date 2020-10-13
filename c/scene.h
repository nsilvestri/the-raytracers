#ifndef _SCENE_H_
#define _SCENE_H_

#include "vec3.h"
#include "ray3.h"
#include "camera.h"
#include "surface.h"

typedef struct scene {
    camera camera;
    surface* surfaces;
    int num_surfaces;
    size_t internal_surface_array_size;
} scene;

scene scene_new();

void scene_add_surface(scene* scene, surface surface);

vec3 scene_color(ray3 r, scene s);

#endif