#include <stdio.h>
#include <stdlib.h>

#include "image.h"

image image_new(int width, int height) {
    image i;
    i.width = width;
    i.height = height;
    // allocate contiguous block for all image data
    i.data = malloc(sizeof(unsigned char) * height * width * 3);
    return i;
}

void image_delete(image i) {
    free(i.data);
}

void image_dump_as_ppm(image i) {
    // write PPM header
    int width = i.width;
    int height = i.height;
    printf("P3\n%d %d\n255\n", width, height);

    size_t image_size = sizeof(unsigned char) * i.width * i.height * 3;
    for (unsigned char* cur = i.data; cur < i.data + image_size; cur+=3) {
        printf("%hhu ", *cur);     // r
        printf("%hhu ", *cur + 1); // g
        printf("%hhu ", *cur + 2); // b
        printf("\n");
    }
}

void image_dump_data(image i) {
    size_t image_size = sizeof(unsigned char) * i.width * i.height * 3;
    for (unsigned char* cur = i.data; cur < i.data + image_size; cur++) {
        printf("%hhu ", *cur);
    }
}