#ifndef _VEC3_H_
#define _VEC3_H_

typedef struct vec3 {
    float x, y, z;
} vec3;

/**
 * @brief Creates a new vec3 struct, populated with the given values. This
 * function allocates space for the new vec3. If space cannot be allocated for
 * this vec3, this function will immediately terminate the program.
 * 
 * @param x the x component of this vec3.
 * @param y the y component of this vec3.
 * @param z the z component of this vec3.
 * @return vec3* a pointer to the newly allocated vec3 struct.
 */
vec3 vec3_new(float x, float y, float z);

/**
 * @brief Return the length of the given vec3.
 * 
 * @param v a pointer to the vec3 struct whose length is desired.
 * @return float the length of the given vec3.
 */
float vec3_length(vec3 v);

/**
 * @brief Perform a scalar multiplication of the given vec3 and scalar value.
 * The result of the scalar multiplication is stored in the vec3* result. 
 * 
 * @param result a pointer to a vec3 struct where the result of the scalar
 *        multiplication is stored. The vec3 struct must already be initialized.
 *        An uninitialized vec3 struct will result in undefined behavior.
 * @param v a pointer to the vec3 struct to perform the scalar multiplication
 *        upon. This struct is not modified.
 * @param scale a float scalar to multiply the given vec3 by.
 * @return vec3* a pointer to the resultant struct. This is always the same
 *        pointer given as the parameter for result.
 */
vec3 vec3_scale(vec3 v, float scale);

/**
 * @brief create a new vector with the same direction, scaled down so that
 *        vec3_length(v) returns 1.0.
 * 
 * @param result a pointer to a vec3 struct where the result of the
 *        normalization is stored. The vec3 struct must already be initialized.
 *        An uninitialized vec3 struct will result in undefined behavior.
 * @param v a pointer to the vec3 struct to normalize. This struct is not
 *        modified.
 * @return vec3* a pointer to the resultant struct. This is always the same
 *        pointer given as the parameter for result.
 */
vec3 vec3_normalize(vec3 v);

/**
 * @brief add two vec3 structs.
 * 
 * @param result a pointer to a vec3 struct which contins the result of the
 *        addition. The vec3 struct must already be initialized. An
 *        uninitialized vec3 struct will result in undefined behavior.
 * @param v1 a pointer to the left operand vec3 struct. This struct is not
 *        modified.
 * @param v2 a pointer to the right operand vec3 struct. This struct is not
 *        modified.
 * @return vec3* a pointer to the resultant struct. This is always the same
 *        pointer given as the parameter for result.
 */
vec3 vec3_add(vec3 v1, vec3 v2);

/**
 * @brief subtract two vec3 structs.
 * 
 * @param result a pointer to a vec3 struct which contins the result of the
 *        subtraction. The vec3 struct must already be initialized. An
 *        uninitialized vec3 struct will result in undefined behavior.
 * @param v1 a pointer to the left operand vec3 struct. This struct is not
 *        modified.
 * @param v2 a pointer to the right operand vec3 struct. This struct is not
 *        modified.
 * @return vec3* a pointer to the resultant struct. This is always the same
 *        pointer given as the parameter for result.
 */
vec3 vec3_sub(vec3 v1, vec3 v2);

/**
 * @brief Return the dot product of two vectors.
 * 
 * @param v1 a vec3 struct pointer for the left side operand of the dot product.
 *        This struct is not modified.
 * @param v2 a vec3 struct pointer for the right side operand of the dot product.
 *        This struct is not modified.
 * @return float the result of the dot product of the two vec3 structs.
 */
float vec3_dot(vec3 v1, vec3 v2);

/**
 * @brief Returns a random vec3 with a length of 1.0 or less. Each component
 *        of the vec3 is in the range [-1, 1], as long as the length of the vec3
 *        is 1.0 or less.
 * 
 * @return vec3* a random vec3 with a length of 1.0 or less.
 */
vec3 vec3_random_in_unit_sphere();

/**
 * @brief Returns a vec3 with each component taken to the power of gamma.
 * 
 * @return vec3* a vec3 with each component taken to the power of gamma.
 */
vec3 vec3_gamma_correct(vec3 color, float gamma);

/**
 * @brief Calculates the vec3 that would be reflected from a given ray and
 * normal.
 * 
 */
vec3 vec3_reflect(vec3 v, vec3 normal);

#endif