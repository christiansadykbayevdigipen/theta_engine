#pragma once

#include "core.h"

#include "vector.h"

/*
@brief A 4 by 4 matrix.
@param matrix The full 4 by 4 matrix representation.
*/
typedef struct {
    f32 matrix[4][4];
}theta_mat4x4f;

/*
@brief This creates an identity matrix.
@returns Returns the identity matrix.
*/
THETA_API theta_mat4x4f theta_mat4x4f_identity();

/*
@brief This creates a copy of a matrix
@param other The other matrix to copy from
@returns The new copied matrix
*/
THETA_API theta_mat4x4f theta_mat4x4f_copy(theta_mat4x4f other);

/*
@brief This performs the addition operation on two matrices.
@param first The first matrix in the addition operation
@param second The second matrix in the addition operation
@returns The result of the operation
*/
THETA_API theta_mat4x4f theta_mat4x4f_add(theta_mat4x4f first, theta_mat4x4f second);

/*
@brief This performs the subtraction operation on two matrices. The order of operations DOES matter in this operation.
@param first The first matrix in the subtraction operation
@param second The second matrix in the subtraction operation
@returns The result of the operation
*/
THETA_API theta_mat4x4f theta_mat4x4f_sub(theta_mat4x4f first, theta_mat4x4f second);

/*
@brief This performs the multiplication operation on two matrices. The order of operations DOES matter in this operation.
@param first The first matrix in the multiplication operation
@param second The second matrix in the multiplication operation
@returns The result of the operation
*/
THETA_API theta_mat4x4f theta_mat4x4f_mul(theta_mat4x4f first, theta_mat4x4f second);

/*
@brief This performs the multiplication operation on a matrix and a float value. 
@param first The first matrix in the multiplication operation
@param scalar The scalar that the first matrix multiplies by
@returns The result of the operation
*/
THETA_API theta_mat4x4f theta_mat4x4f_muls(theta_mat4x4f first, f32 scalar);

/*
@brief This performs the division operation on a matrix and a float value. 
@param first The first matrix in the division operation
@param scalar The scalar that the first matrix divides by
@returns The result of the operation
*/
THETA_API theta_mat4x4f theta_mat4x4f_divs(theta_mat4x4f first, f32 scalar);

/*Projection Matrix Generators*/

/*
@brief This creates an orthographic projection matrix.
@returns The resulting matrix.
*/
THETA_API theta_mat4x4f theta_mat4x4f_orthographic();

/*
@brief This creates an orthographic projection matrix with special arguments.
@returns The resulting matrix.
*/
THETA_API theta_mat4x4f theta_mat4x4f_orthographic_args(f32 left, f32 right, f32 bottom, f32 top, f32 near, f32 far);

THETA_API theta_mat4x4f theta_mat4x4f_perspective();

// TODO: Add perspective projection matricies

/*
@brief Translates a matrix by a vector
@param first The matrix being translated
@param vector The vector that the matrix is being translated by
@returns The resulting matrix of the operation
*/
THETA_API theta_mat4x4f theta_mat4x4f_translate(theta_mat4x4f first, theta_vector3f vector);

/*
@brief Rotates a matrix by a vector
@param first The matrix being rotated
@param vector The vector that the matrix is being rotated by
@returns The resulting matrix of the operation
*/
THETA_API theta_mat4x4f theta_mat4x4f_rotate(theta_mat4x4f first, theta_vector3f vector);

/*
@brief Scales a matrix by a vector
@param first The matrix being scaled
@param vector The vector that the matrix is being scaled by
@returns The resulting matrix of the operation
*/
THETA_API theta_mat4x4f theta_mat4x4f_scale(theta_mat4x4f first, theta_vector3f vector);

/*
@brief Scales a matrix by a scalar value
@param first The matrix being scaled
@param scalar The scalar value that the matrix is being scaled by
@returns The resulting matrix of the operation
*/
THETA_API theta_mat4x4f theta_mat4x4f_scales(theta_mat4x4f first, f32 scalar);

/*
@brief This transforms a vector by some transformation matrix.
@param matrix The transformation matrix to transform the vector
@param vector The vector that is being transformed by the matrix
@returns The resulting vector of the operation
*/
THETA_API theta_vector3f theta_mat4x4f_transform_vector(theta_mat4x4f matrix, theta_vector3f vector);