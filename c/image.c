#include <stdio.h>
#include <stdlib.h>

#include "image.h"

image* image_new(int width, int height) {
    image* i = malloc(sizeof(image));
    i->width = width;
    i->height = height;
    // allocate space for each row
    i->data = malloc(sizeof(unsigned char) * height * width * 3);
    return i;
}

void image_dump_as_ppm(image* i) {
    // write PPM header
    int width = i->width;
    int height = i->height;
    printf("P3\n%d %d\n255\n", width, height);

    for (int x = 0; x < i->width; x++) {
        for (int y = 0; y < i->height; y++) {
            // write pixel color to file
            printf("%d %d %d\n", (int) (i->data[y + (x * 3) + 0]), (int) (i->data[y + (x * 3) + 1]), (int) (i->data[y + (x * 3) + 2]));
        }
    }
}

void image_dump_data(image* i) {
    for (int x = 0; x < i->width; x++) {
        for (int y = 0; y < i->height; y++) {
            // write pixel color to file
            unsigned char r = i->data[(y * i->width) + (x * 3) + 0];
            unsigned char g = i->data[(y * i->width) + (x * 3) + 1];
            unsigned char b = i->data[(y * i->width) + (x * 3) + 2];
            fprintf(stderr, "%d %d %d ", (int) r, (int) g, (int) b);
            // printf("%d %d %d ", (int) r, (int) g, (int) b);
        }
        // printf("\n");
        fprintf(stderr, "\n");
    }
}