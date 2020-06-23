#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <time.h>

#include "vec3.h"
#include "ray3.h"
#include "scene.h"
#include "surface.h"
#include "image.h"

#define THREADS 4

typedef struct render_args {
    int* bounds;
    image image;
    scene scene;
    int samples;
} render_args;

void* render(void* parameter);

// benchmarking func
struct timespec diff(struct timespec start, struct timespec end);

int main(int argc, char** argv) {
    // seed random number generator
    srand48(time(NULL));

    // set image properties
    int image_width = 800;
    int image_height = 400;
    image output_image = image_new(image_width, image_height);

    // create scene
    scene scene = scene_new();

    // benchmarking
    struct timespec start;
    clock_gettime(CLOCK_REALTIME, &start);

    // render
    int num_samples = 10;
    pthread_t threads[THREADS];
    for (int i = 0; i < THREADS; i++) {
        pthread_t thread;
        render_args parameter;
        int bounds[] = { image_width / THREADS * i, image_width / THREADS, 0, image_height };
        parameter.bounds = bounds;
        parameter.bounds = NULL;
        parameter.image = output_image;
        parameter.scene = scene;
        parameter.samples = num_samples;
        threads[i] = pthread_create(&thread, NULL, render, &parameter);
    }
    // wait for all threads to finish
    for (int i = 0; i < THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // end benchmark
    struct timespec stop;
    clock_gettime(CLOCK_REALTIME, &stop);

    // output benchmark
    struct timespec total = diff(start, stop);
    fprintf(stderr, "Total time: %d.%d seconds\n", (int) total.tv_sec, (int) total.tv_nsec);
    fprintf(stderr, "Samples per second: %f\n", (float) (image_height * image_width * num_samples) / (total.tv_sec + ((float) total.tv_nsec / 1000000000)));

    // write file to output
    image_dump_as_ppm(output_image);
    image_delete(output_image);
    return 0;
}

void* render(void* parameter) {
    render_args* args = (render_args*)parameter;
    int* bounds = args->bounds;
    image image = args->image;
    scene scene = args->scene;
    int num_samples = args->samples;

    int x1, x2, y1, y2;

    if (bounds != NULL) {
        x1 = bounds[0];
        x2 = bounds[1];
        y1 = bounds[2];
        y2 = bounds[3];
    }
    else {
        x1 = 0;
        x2 = image.width;
        y1 = 0;
        y2 = image.height;
    }

    // X-axis is left, Y is up, -Z is towards the screen
    vec3 lower_left_corner = vec3_new(-2.0, -1.0, -1.0);
    vec3 horizontal = vec3_new(4.0, 0.0, 0.0);
    vec3 vertical = vec3_new(0.0, 2.0, 0.0);
    vec3 origin = vec3_new(0.0, 0.0, 0.0);

    // iterate over each pixel. Starts at bottom left as 0,0
    for (int y = y1; y < y2; y++) {
        // and left to right
        for (int x = x1; x < x2; x++) {
            // create a vec3 to store the total color of this pixel
            vec3 pixel_color = vec3_new(0, 0, 0);

            // sample this pixel num_sample times
            for (int s = 0; s < num_samples; s++) {
                // u and v are percentages of the width and height of the image
                // randomness chooses a random point within the square of the pixel
                float u = ((float) x / (x2 - x1)) + (drand48() / (x2 - x1)); 
                float v = ((float) y / (y2 - y1)) + (drand48() / (y2 - y1));
                
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
                vec3 color_sample = scene_color(r, scene.surfaces, scene.num_surfaces);

                // gamma correct sample
                vec3 color_sample_gamma = vec3_gamma_correct(color_sample, 0.5);

                // add sample color to color total for this pixel
                pixel_color = vec3_add(pixel_color, color_sample_gamma);
            }
            
            // pixel_color contains the total of all samples; get the average of each sample
            pixel_color = vec3_scale(pixel_color, 1.0 / num_samples);

            // store in image_data
            unsigned char r = pixel_color.x * 255;
            unsigned char g = pixel_color.y * 255;
            unsigned char b = pixel_color.z * 255;
            int image_y = image.height - y - 1; // y is flipped because origin is top-left in image coords
            image.data[(image_y * image.width * 3) + (x * 3) + 0] = r;
            image.data[(image_y * image.width * 3) + (x * 3) + 1] = g;
            image.data[(image_y * image.width * 3) + (x * 3) + 2] = b;
        }
    }
    return NULL; // void* functions require some return
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

     
