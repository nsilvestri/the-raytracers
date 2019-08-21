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

    // write PPM header
    printf("P3\n%d %d\n255\n", image_width, image_height);

    // X-axis is left, Y is up, -Z is towards the screen
    vec3* lower_left_corner = vec3_make(-2.0, -1.0, -1.0);
    vec3* horizontal = vec3_make(4.0, 0.0, 0.0);
    vec3* vertical = vec3_make(0.0, 2.0, 0.0);
    vec3* origin = vec3_make(0.0, 0.0, 0.0);

    // manually add surfaces (for now)
    surface* sphere = surface_sphere_make(vec3_make(0, 0, -1), 0.5);
    surface* sphere_big = surface_sphere_make(vec3_make(0, -100.5, -1), 100);
    surface* surfaces[2] = { sphere, sphere_big };

    // iterate over each pixel, from top to bottom (because of PPM pixel order)
    for (int j = image_height - 1; j >= 0; j--) {
        // and left to right
        for (int i = 0; i < image_width; i++) {
            // create a vec3 to store the total color of this pixel
            vec3* pixel_color = vec3_make(0, 0, 0);

            // sample this pixel num_sample times
            for (int s = 0; s < num_samples; s++) {
                // u and v are percentages of the width and height of the image
                // randomness chooses a random point within the square of the pixel
                float u = ((float) i / image_width) + (drand48() / image_width); 
                float v = ((float) j / image_height) + (drand48() / image_height);
                
                // vec3 component for how for how far right to push our final ray
                vec3* horizontal_offset = vec3_scale(vec3_make(0, 0, 0), horizontal, u);

                // vec3 component for how far up to push our final ray
                vec3* vertical_offset = vec3_scale(vec3_make(0, 0, 0), vertical, v);

                // combine the two components above
                vec3* total_offset = vec3_add(vec3_make(0, 0, 0), horizontal_offset, vertical_offset);

                // and add it to our lower-left corner to get the final direction
                vec3* direction = vec3_add(vec3_make(0, 0, 0), lower_left_corner, total_offset);

                // create the ray with our camera position (origin) and calculated direction
                ray3* r = ray3_make(origin, direction);

                // get our color sample for our single ray from the world
                vec3* color_sample = scene_color(r, surfaces, 2);

                // add sample color to color total for this pixel
                pixel_color = vec3_add(pixel_color, pixel_color, color_sample);

                // clean up
                free(horizontal_offset);
                free(vertical_offset);
                free(total_offset);

                free(direction);
                free(r); // direction is freed explicitly above; origin is used later so don't free

                free(color_sample);
            }
            
            // pixel_color contains the total of all samples; get the average of each sample
            pixel_color = vec3_scale(pixel_color, pixel_color, 1.0 / num_samples);

            // write pixel color to file
            printf("%d %d %d\n", (int) (pixel_color->x * 255), (int) (pixel_color->y * 255), (int) (pixel_color->z * 255));

            // clean up
            free(pixel_color);
        }
    }

    // clean up
    free(lower_left_corner);
    free(horizontal);
    free(vertical);
    free(origin);

    free(sphere->sphere_origin);
    free(sphere);

    free(sphere_big->sphere_origin);
    free(sphere_big);
}

     
