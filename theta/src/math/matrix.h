#pragma once

#include "core.h"

#include "vector.h"

// Basic 4x4 matrix structure
typedef struct {
    f32 matrix[4][4];
}theta_mat4x4f;

// Creates an identity matrix
THETA_API theta_mat4x4f theta_mat4x4f_identity();

// Copies a matrix over
THETA_API theta_mat4x4f theta_mat4x4f_copy(theta_mat4x4f other);

// Adds two matrices together.
THETA_API theta_mat4x4f theta_mat4x4f_add(theta_mat4x4f first, theta_mat4x4f second);

// Sutracts two matrices together. The order of operations is important
THETA_API theta_mat4x4f theta_mat4x4f_sub(theta_mat4x4f first, theta_mat4x4f second);

// Multiplies two matrices together. The order of operations is important
THETA_API theta_mat4x4f theta_mat4x4f_mul(theta_mat4x4f first, theta_mat4x4f second);

// Multiplies a matrix by a single floating point scalar value
THETA_API theta_mat4x4f theta_mat4x4f_muls(theta_mat4x4f first, f32 scalar);

// Divides a matrix by a single floating point scalar value
THETA_API theta_mat4x4f theta_mat4x4f_divs(theta_mat4x4f first, f32 scalar);

// Creates an orthographic projection matrix with default parameters
THETA_API theta_mat4x4f theta_mat4x4f_orthographic();

// Creates an orthographic projection matrix with specified parameters
THETA_API theta_mat4x4f theta_mat4x4f_orthographic_args(f32 left, f32 right, f32 bottom, f32 top, f32 near, f32 far);

// Creates a perspective projection matrix with default parameters
THETA_API theta_mat4x4f theta_mat4x4f_perspective();

// TODO: Add perspective projection matricies

// Translates a matrix by a vector
THETA_API theta_mat4x4f theta_mat4x4f_translate(theta_mat4x4f first, theta_vector3f vector);

// Rotates a matrix by a vector
THETA_API theta_mat4x4f theta_mat4x4f_rotate(theta_mat4x4f first, theta_vector3f vector);

// Scales a matrix by a vector
THETA_API theta_mat4x4f theta_mat4x4f_scale(theta_mat4x4f first, theta_vector3f vector);

// Scales a matrix by a single floating point scalar value
THETA_API theta_mat4x4f theta_mat4x4f_scales(theta_mat4x4f first, f32 scalar);

// Transforms a matrix by a vector
THETA_API theta_vector3f theta_mat4x4f_transform_vector(theta_mat4x4f matrix, theta_vector3f vector);