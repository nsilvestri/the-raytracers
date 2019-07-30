#include <stdio.h>
#include <stdlib.h>
#include "ray3.h"

ray3* ray3_make(vec3* origin, vec3* direction) {
    ray3* r = malloc(sizeof(ray3));
    if (r == NULL) {
        fprintf(stderr, "Out of memory\n");
        exit(1);
    }
    r->origin = origin;
    r->direction = direction;
    return r;
}