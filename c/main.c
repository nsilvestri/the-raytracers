#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "vec3.h"
#include "ray3.h"
#include "scene.h"
#include "surface.h"

// benchmarking func
struct timespec diff(struct timespec start, struct timespec end);

int main(int argc, char** argv) {
    // seed random number generator
    srand48(time(NULL));

    // set image properties
    int image_width = 800;
    int image_height = 400;
    int num_samples = 1000;

    // write PPM header
    printf("P3\n%d %d\n255\n", image_width, image_height);

    // X-axis is left, Y is up, -Z is towards the screen
    vec3 lower_left_corner = vec3_new(-2.0, -1.0, -1.0);
    vec3 horizontal = vec3_new(4.0, 0.0, 0.0);
    vec3 vertical = vec3_new(0.0, 2.0, 0.0);
    vec3 origin = vec3_new(0.0, 0.0, 0.0);

    // manually add surfaces (for now)
    int num_surfaces = 4;
    material rough_copper = material_metal_new(0.7, vec3_new(1.0, 0.4, 0.05), 0.8);
    material mirror = material_metal_new(0.99, vec3_new(0, 0, 0), 0.0);
    material green_matte = material_lambertian_new(0.5, vec3_new(0.8, 0.8, 0.0));
    material red_matte = material_lambertian_new(0.5, vec3_new(1.0, 0.3, 0.3));
    surface sphere_big = surface_sphere_new(vec3_new(0, -100.5, -1), 100, green_matte);
    surface sphere_red = surface_sphere_new(vec3_new(-1.0, 0, -1), 0.5, red_matte);
    surface sphere_copper = surface_sphere_new(vec3_new(0, -0.1, -1), 0.4, rough_copper);
    surface sphere_mirror = surface_sphere_new(vec3_new(0.75, -0.2, -0.5), 0.3, mirror);
    surface surfaces[4] = { sphere_big, sphere_red, sphere_copper, sphere_mirror };

    // benchmarking
    struct timespec start;
    clock_gettime(CLOCK_REALTIME, &start);

    // iterate over each pixel, from top to bottom (because of PPM pixel order)
    for (int j = image_height - 1; j >= 0; j--) {
        // and left to right
        for (int i = 0; i < image_width; i++) {
            // create a vec3 to store the total color of this pixel
            vec3 pixel_color = vec3_new(0, 0, 0);

            // sample this pixel num_sample times
            for (int s = 0; s < num_samples; s++) {
                // u and v are percentages of the width and height of the image
                // randomness chooses a random point within the square of the pixel
                float u = ((float) i / image_width) + (drand48() / image_width); 
                float v = ((float) j / image_height) + (drand48() / image_height);
                
                // vec3 component for how for how far right to push our final ray
                vec3 horizontal_offset = vec3_scale(horizontal, u);

                // vec3 component for how far up to push our final ray
                vec3 vertical_offset = vec3_scale(vertical, v);

                // combine the two components above
                vec3 total_offset = vec3_add(horizontal_offset, vertical_offset);

                // and add it to our lower-left corner to get the final direction
                vec3 direction = vec3_add(lower_left_corner, total_offset);

                // create the ray with our camera position (origin) and calculated direction
                ray3 r = ray3_new(origin, direction);

                // get our color sample for our single ray from the world
                vec3 color_sample = scene_color(r, surfaces, num_surfaces);

                // gamma correct sample
                vec3 color_sample_gamma = vec3_gamma_correct(color_sample, 0.5);

                // add sample color to color total for this pixel
                pixel_color = vec3_add(pixel_color, color_sample_gamma);

            }
            
            // pixel_color contains the total of all samples; get the average of each sample
            pixel_color = vec3_scale(pixel_color, 1.0 / num_samples);

            // write pixel color to file
            printf("%d %d %d\n", (int) (pixel_color.x * 255), (int) (pixel_color.y * 255), (int) (pixel_color.z * 255));
        }
    }

    // end benchmark
    struct timespec stop;
    clock_gettime(CLOCK_REALTIME, &stop);
    time_t end = time(NULL);

    // output benchmark
    struct timespec total = diff(start, stop);
    fprintf(stderr, "Total time: %d.%d seconds\n", total.tv_sec, total.tv_nsec);
    fprintf(stderr, "Samples per second: %f\n", (float) (image_height * image_width * num_samples) / (total.tv_sec + ((float) total.tv_nsec / 1000000000)));
}

/**
 * @brief Take the difference between two struct timespec.
 * 
 * Code taken from guyrutenberg.com
 * 
 * @param start 
 * @param end 
 * @return struct timespec 
 */

struct timespec diff(struct timespec start, struct timespec end)
{
	struct timespec temp;
	if ((end.tv_nsec-start.tv_nsec)<0) {
		temp.tv_sec = end.tv_sec-start.tv_sec-1;
		temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
	} else {
		temp.tv_sec = end.tv_sec-start.tv_sec;
		temp.tv_nsec = end.tv_nsec-start.tv_nsec;
	}
	return temp;
}

     
