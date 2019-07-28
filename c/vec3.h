#ifndef _VECTOR3D_H_
#define _VECTOR3D_H_

typedef struct vec3 {
    float x, y, z;
} vec3;

vec3* vec3_make(float x, float y, float z);

float vec3_length(vec3* v);
vec3 vec3_normalize(vec3* v);

float vec3_dot(vec3* v1, vec3* v2);
vec3* vec3_cross(vec3* v1, vec3* v2);

#endif
