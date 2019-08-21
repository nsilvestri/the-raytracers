#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "vec3.h"
#include "ray3.h"
#include "scene.h"
#include "surface.h"


int main(int argc, char** argv) {
    // seed random number generator
    srand48(time(NULL));

    // set image properties
    int image_width = 400;
    int image_height = 200;
    int num_samples = 30;

    printf("P3\n%d %d\n255\n", image_width, image_height);

    // X-axis is left, Y is up, -Z is towards the screen
    vec3* lower_left_corner = vec3_make(-2.0, -1.0, -1.0);
    vec3* horizontal = vec3_make(4.0, 0.0, 0.0);
    vec3* vertical = vec3_make(0.0, 2.0, 0.0);
    vec3* origin = vec3_make(0.0, 0.0, 0.0);

    surface* sphere = surface_sphere_make(vec3_make(0, 0, -1), 0.5);
    surface* sphere_big = surface_sphere_make(vec3_make(0, -100.5, -1), 100);
    surface* surfaces[2] = { sphere, sphere_big };

    for (int j = image_height - 1; j >= 0; j--) {
        for (int i = 0; i < image_width; i++) {
            vec3* color = vec3_make(0, 0, 0);
            // sample this pixel num_sample times
            for (int s = 0; s < num_samples; s++) {
                // u and v are percentages of the width and height of the image
                float u = ((float) i / image_width) + (drand48() / image_width); 
                float v = ((float) j / image_height) + (drand48() / image_height);
                
                vec3* horizontal_offset = vec3_make(0, 0, 0);
                horizontal_offset = vec3_scale(horizontal_offset, horizontal, u);

                vec3* vertical_offset = vec3_make(0, 0, 0);
                vertical_offset = vec3_scale(vertical_offset, vertical, v);

                vec3* total_offset = vec3_make(0, 0, 0);
                total_offset = vec3_add(total_offset, horizontal_offset, vertical_offset);

                vec3* direction = vec3_make(0, 0, 0);
                direction = vec3_add(direction, lower_left_corner, total_offset);

                ray3* r = ray3_make(origin, direction);

                vec3* color_sample = scene_color(r, surfaces, 2);

                // add sample color to color total
                color = vec3_add(color, color, color_sample);

                // clean up
                free(horizontal_offset);
                free(vertical_offset);
                free(total_offset);
                free(direction);
                free(r);
                free(color_sample);
            }
            
            // take average of each sample color
            color = vec3_scale(color, color, 1.0 / num_samples);

            // write pixel color to file
            printf("%d %d %d\n", (int) (color->x * 255), (int) (color->y * 255), (int) (color->z * 255));

            // clean up
            free(color);
        }
    }
}

     
