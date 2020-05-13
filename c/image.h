#ifndef _IMAGE_H_
#define _IMAGE_H_

typedef struct image {
    int width;
    int height;
    char* data;
} image;

image* image_new(int width, int height);

void image_dump_as_ppm(image* i);

void image_dump_data(image* i);

#endif