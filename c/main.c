#include <stdio.h>

#include "vec3.h"
#include "ray3.h"
#include "surface.h"

int main(int argc, char** argv) {
    int image_width = 200;
    int image_height = 100;

    printf("P3\n%d %d\n255\n", image_width, image_height);

    // X-axis is left, Y is up, -Z is towards the screen
    vec3* lower_left_corner = vec3_make(-2.0, -1.0, -1.0);
    vec3* horizontal = vec3_make(4.0, 0.0, 0.0);
    vec3* vertical = vec3_make(0.0, 2.0, 0.0);
    vec3* origin = vec3_make(0.0, 0.0, 0.0);

    surface* sphere = surface_sphere_make(vec3_make(0, 0, -1), 0.5);

    for (int j = 0; j < image_height; j++) {
        for (int i = 0; i < image_width; i++) {
            float u = (float) i / (float) image_width; 
            float v = (float) j / (float) image_height;
            vec3* horizontal_offset = vec3_scale(horizontal, u);
            vec3* vertical_offset = vec3_scale(vertical, v);
            vec3* direction = vec3_add(lower_left_corner,
                                       vec3_add(horizontal_offset, vertical_offset));
            ray3* r = ray3_make(origin, direction);
            vec3* color = surface_intersect(sphere, r);
            printf("%d %d %d\n", (int) (color->r * 255), (int) (color->g * 255), (int) (color->b * 255));
        }
    }
}

     
