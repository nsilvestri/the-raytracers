#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "vec3.h"
#include "ray3.h"
#include "surface.h"


int main(int argc, char** argv) {
    // seed random number generator
    srand48(time(NULL));

    // set image properties
    int image_width = 200;
    int image_height = 100;
    int num_samples = 20;

    printf("P3\n%d %d\n255\n", image_width, image_height);

    // X-axis is left, Y is up, -Z is towards the screen
    vec3* lower_left_corner = vec3_make(-2.0, -1.0, -1.0);
    vec3* horizontal = vec3_make(4.0, 0.0, 0.0);
    vec3* vertical = vec3_make(0.0, 2.0, 0.0);
    vec3* origin = vec3_make(0.0, 0.0, 0.0);

    surface* sphere = surface_sphere_make(vec3_make(0, 0, -1), 0.5);

    for (int j = 0; j < image_height; j++) {
        for (int i = 0; i < image_width; i++) {
            vec3* color = vec3_make(0, 0, 0);
            for (int s = 0; s < num_samples; s++) {
                float u = ((float) i / image_width) + (drand48() / image_width); 
                float v = ((float) j / image_height) + (drand48() / image_height);
                vec3* horizontal_offset = vec3_scale(horizontal, u);
                vec3* vertical_offset = vec3_scale(vertical, v);
                vec3* direction = vec3_add(lower_left_corner,
                                        vec3_add(horizontal_offset, vertical_offset));
                ray3* r = ray3_make(origin, direction);
                hit_record* hit_record = surface_hit(sphere, r);
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
                // add sample color to color total
                color = vec3_add(color, color_sample);
            }
            // take average of each sample color
            color = vec3_scale(color, 1.0 / num_samples);

            // write pixel color to file
            printf("%d %d %d\n", (int) (color->x * 255), (int) (color->y * 255), (int) (color->z * 255));
        }
    }
}

     
