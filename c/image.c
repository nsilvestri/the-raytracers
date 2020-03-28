#include "image.h"

image image_new(int width, int height) {
    image i;
    i.width = width;
    i.height = height;
    i.data = malloc(sizeof(char) * width * height * 3);
    return i;
}

void image_dump_as_ppm(image i) {
    // write PPM header
    printf("P3\n%d %d\n255\n", i.width, i.height);

    for (int x = 0; x < i.width; x++) {
        for (int y = 0; y < i.height; y++) {
            // write pixel color to file
            printf("%d %d %d\n", (int) (i.data[y][x][0]), (int) (i.data[y][x][1]), (int) (i.data[y][x][2]));
        }
    }
}