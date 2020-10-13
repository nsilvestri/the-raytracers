#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <math.h>
#include <time.h>

#include "vec3.h"
#include "ray3.h"
#include "scene.h"
#include "surface.h"
#include "image.h"

#define NUM_THREADS 1

typedef struct render_args {
    int* bounds;
    image image;
    scene scene;
    int samples;
} render_args;

/* Using a linked list for storing our running list of materials while parsing
 * the scene file
 */
typedef struct material_ll_node {
    material* material;
    struct material_ll_node* next;
} material_ll_node;
material_ll_node* material_ll_add(material_ll_node* node, material* new_material);
material* find_material(material_ll_node* node, char* material_name);

void* render(void* parameter);
scene read_scene_file(char* filename);

// benchmarking func
struct timespec diff(struct timespec start, struct timespec end);

// values set while reading scene file, to be accessible from main()
int image_width;
int image_height;
int num_samples;

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage:\n");
        printf("  ./prog01 scene_file > output_file\n");
        exit(1);
    }
    // seed random number generator
    srand48(time(NULL));

    // create scene and image
    scene scene = read_scene_file(argv[1]);
    image output_image = image_new(image_width, image_height);

    // benchmarking
    struct timespec start;
    clock_gettime(CLOCK_REALTIME, &start);

    // render
    int num_samples = 10;
    pthread_t threads[NUM_THREADS];
    render_args parameters[NUM_THREADS];
    for (int i = 0; i < NUM_THREADS; i++) {
        int bounds[] = { image_width / NUM_THREADS * i, image_width / NUM_THREADS, 0, image_height };
        parameters[i].bounds = bounds;
        parameters[i].bounds = NULL;
        parameters[i].image = output_image;
        parameters[i].scene = scene;
        parameters[i].samples = num_samples;
        pthread_create(&threads[i], NULL, render, &parameters[i]);
    }
    // wait for all threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
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
    vec3 lower_left_corner = scene.camera.lower_left_corner;
    vec3 horizontal = scene.camera.horizontal;
    vec3 vertical = scene.camera.vertical;
    vec3 origin = scene.camera.position;

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
                vec3 color_sample = scene_color(r, scene);

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

scene read_scene_file(char* filename) {
    scene s = scene_new();

    material_ll_node* materials = NULL;

    char* line = NULL;
    size_t len = 0;
    size_t chars_read;
    FILE* input_file = fopen(filename, "r");

    if (input_file == NULL) {
        fprintf(stderr, "There was an error opening the file: %s\n", filename);
        exit(1);
    }

    while ((chars_read = getline(&line, &len, input_file)) != -1) {
        char* delimiters = " \n";
        char* token = strtok(line, delimiters);
        if (token == NULL) continue;
        char first_char = *token;
        switch (first_char) {
            case '\n':
            case '#':
                // comment line; skip
                break;
            case 'i': {
                image_width = strtol(strtok(NULL, delimiters), NULL, 10);
                image_height = strtol(strtok(NULL, delimiters), NULL, 10);
                break;
            }
            case 's': {
                num_samples = strtol(strtok(NULL, delimiters), NULL, 10);
                break;
            }
            case 'e': {
                float x = strtof(strtok(NULL, delimiters), NULL);
                float y = strtof(strtok(NULL, delimiters), NULL);
                float z = strtof(strtok(NULL, delimiters), NULL);
                s.camera.position = vec3_new(x, y, z);
                break;
            }
            case 'l': {
                float x1 = strtof(strtok(NULL, delimiters), NULL);
                float y1 = strtof(strtok(NULL, delimiters), NULL);
                float z1 = strtof(strtok(NULL, delimiters), NULL);
                float x2 = strtof(strtok(NULL, delimiters), NULL);
                float y2 = strtof(strtok(NULL, delimiters), NULL);
                float z2 = strtof(strtok(NULL, delimiters), NULL);
                float x3 = strtof(strtok(NULL, delimiters), NULL);
                float y3 = strtof(strtok(NULL, delimiters), NULL);
                float z3 = strtof(strtok(NULL, delimiters), NULL);
                vec3 lower_left_corner = vec3_new(x1, y1, z1);
                vec3 horizontal = vec3_new(x2, y2, z2);
                vec3 vertical = vec3_new(x3, y3, z3);
                s.camera.lower_left_corner = lower_left_corner;
                s.camera.horizontal = horizontal;
                s.camera.vertical = vertical;
                break;
            }
            case 'M': {
                char* materialName = strtok(NULL, delimiters);
                float albedo = strtof(strtok(NULL, delimiters), NULL);
                float r = strtof(strtok(NULL, delimiters), NULL);
                float g = strtof(strtok(NULL, delimiters), NULL);
                float b = strtof(strtok(NULL, delimiters), NULL);
                char* roughness_str = strtok(NULL, delimiters); // might be NULL, will be checked before converting to float
                material* new_material;
                if (roughness_str != NULL) {
                    double roughness = strtof(roughness_str, NULL);
                    new_material = material_metal_new(materialName, albedo, vec3_new(r, g, b), roughness);
                } else {
                    new_material = material_lambertian_new(materialName, albedo, vec3_new(r, g, b));
                }

                material_ll_node* new_node = material_ll_add(materials, new_material);
                if (materials == NULL) {
                    materials = new_node;
                }
                break;
            }
            case 'S': {
                float x = strtof(strtok(NULL, delimiters), NULL);
                float y = strtof(strtok(NULL, delimiters), NULL);
                float z = strtof(strtok(NULL, delimiters), NULL);
                float radius = strtof(strtok(NULL, delimiters), NULL);
                char* material_name = strtok(NULL, delimiters);
                surface new_sphere = surface_sphere_new(vec3_new(x, y, z), radius, *(find_material(materials, material_name)));
                scene_add_surface(&s, new_sphere);
                break;
            }
            default: {
                fprintf(stderr, "Unrecognized line operation in %s: %c", input_file, first_char);
                break;
            }
        }
    }

    fclose(input_file);
    if (line) {
        free(line);
    }

    return s;
}

material_ll_node* material_ll_add(material_ll_node* node, material* new_material) {
    // base case for an empty starting node
    if (node == NULL) {
        node = malloc(sizeof(material_ll_node));
        node->material = new_material;
        node->next = NULL;
        return node;
    }

    // go to the last node
    while (node->next != NULL) {
        node = node->next;
    }
    // create a new node
    material_ll_node* new_node;
    new_node = malloc(sizeof(material_ll_node));
    new_node->material = new_material;
    new_node->next = NULL;

    // add it to the end of the list
    node->next = new_node;

    return new_node;
}

material* find_material(material_ll_node* node, char* material_name) {
    material_ll_node* current_node = node;
    while (current_node != NULL) {
        if (strcmp(current_node->material->name, material_name) == 0) {
            return current_node->material;
        }
        current_node = current_node->next;
    }
    return NULL;
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

     
