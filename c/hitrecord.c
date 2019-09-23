#include <stdlib.h>
#include <stdio.h>

#include "hitrecord.h"
#include "vec3.h"

hit_record hit_record_new(float t, vec3 normal) {
    hit_record hr;
    hr.t = t;
    hr.normal = normal;
    return hr;
}