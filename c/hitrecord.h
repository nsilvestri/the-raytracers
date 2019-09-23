#ifndef _HITRECORD_H_
#define _HITRECORD_H_

#include "vec3.h"

typedef struct hit_record {
    float t;
    vec3* normal;
} hit_record;

hit_record* hit_record_new(float t, vec3* normal);

#endif 