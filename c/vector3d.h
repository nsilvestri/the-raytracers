#ifndef _VECTOR3D_H_
#define _VECTOR3D_H_

typedef struct vector3d {
    float x, y, z;
} vector3d;

vector3d* vector3d_make(float x, float y, float z);

float vector3d_length(vector3d* v);
vector3d vector3d_normalize(vector3d* v);

float vector3d_dot(vector3d* v1, vector3d* v2);
vector3d* vector3d_cross(vector3d* v1, vector3d* v2);

#endif
