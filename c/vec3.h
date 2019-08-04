#ifndef _VEC3_H_
#define _VEC3_H_

typedef struct vec3 {
    float x, y, z;
    float r, g, b;
} vec3;

vec3* vec3_make(float x, float y, float z);
vec3* rgb_make(float r, float g, float b);

float vec3_length(vec3* v);
vec3* vec3_normalize(vec3* v);

vec3* vec3_scale(vec3* v, float scale);
vec3* vec3_add(vec3* v1, vec3* v2);
vec3* vec3_sub(vec3* v1, vec3* v2);
float vec3_dot(vec3* v1, vec3* v2);
vec3* vec3_cross(vec3* v1, vec3* v2);

#endif
