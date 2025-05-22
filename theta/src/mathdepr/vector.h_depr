#pragma once

#include "core.h"

/*
@brief This is a basic mathematical representation of a three dimensional vector
@param x The x component of the vector
@param y The y component of the vector
@param z The z component of the vector
*/
typedef struct {
    f32 x, y, z;
}theta_vector3f;

/*
@brief This initializes a vector with zero values for x, y, and z.
@returns The initialized vector
*/
THETA_API theta_vector3f theta_vector3f_create();

/*
@brief This initializes a vector with arguments.
@param x The x component of the vector
@param y The y component of the vector
@param z The z component of the vector
@returns The initialized vector
*/
THETA_API theta_vector3f theta_vector3f_create_args(f32 x, f32 y, f32 z);

/*
@brief Performs the addition operation between two vectors.
@param first The first vector in the operation
@param second The second vector in the operation
*/
THETA_API theta_vector3f theta_vector3f_add(theta_vector3f first, theta_vector3f second);

/*
@brief Performs the subtraction operation between two vectors. The order of operations DOES matter in this operation.
@param first The first vector in the operation
@param second The second vector in the operation
*/
THETA_API theta_vector3f theta_vector3f_sub(theta_vector3f first, theta_vector3f second);

/*
@brief Performs the multiplication operation between two vectors.
@param first The first vector in the operation
@param second The second vector in the operation
*/
THETA_API theta_vector3f theta_vector3f_mul(theta_vector3f first, theta_vector3f second);

/*
@brief Performs the multiplication operation between a vector and a scalar
@param first The first vector in the operation
@param scalar The scalar value in the operation
*/
THETA_API theta_vector3f theta_vector3f_muls(theta_vector3f first, f32 scalar);

/*
@brief Performs the division operation between two vectors. The order of operations DOES matter in this operation.
@param first The first vector in the operation
@param second The second vector in the operation
*/
THETA_API theta_vector3f theta_vector3f_div(theta_vector3f first, theta_vector3f second);

/*
@brief Performs the division operation between a vector and a scalar. The order of operations DOES matter in this operation.
@param first The first vector in the operation
@param scalar The scalar value in the operation
*/
THETA_API theta_vector3f theta_vector3f_divs(theta_vector3f first, f32 scalar);

// TODO: Add the other important vector functions like dot product, cross product, etc.