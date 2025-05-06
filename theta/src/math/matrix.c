#include "matrix.h"


#include <math.h>

theta_mat4x4f theta_mat4x4f_identity() {
    theta_mat4x4f matrix;
    
    // Initialize all matrix values to 0
    for(u32 i = 0; i < 4; i++) {
        for(u32 j = 0; j < 4; j++) {
            matrix.matrix[i][j] = 0.0f;
        }
    }

    // Initialize matrix values in a diagonal line to 1
    // I could theoretically use a for loop for this, but this has better runtime performance.
    matrix.matrix[0][0] = 1.0f;
    matrix.matrix[1][1] = 1.0f;
    matrix.matrix[2][2] = 1.0f;
    matrix.matrix[3][3] = 1.0f;
}

theta_mat4x4f theta_mat4x4f_copy(theta_mat4x4f other) {
    theta_mat4x4f new_matrix;

    for(u32 i = 0; i < 4; i++) {
        for(u32 j = 0; j < 4; j++) {
            new_matrix.matrix[i][j] = other.matrix[i][j];
        }
    }

    return new_matrix;
}

theta_mat4x4f theta_mat4x4f_add(theta_mat4x4f first, theta_mat4x4f second) {
    theta_mat4x4f result;

    for(u32 i = 0; i < 4; i++) {
        for(u32 j = 0; j < 4; j++) {
            result.matrix[i][j] = first.matrix[i][j] + second.matrix[i][j];
        }
    }

    return result;
}

theta_mat4x4f theta_mat4x4f_sub(theta_mat4x4f first, theta_mat4x4f second) {
    theta_mat4x4f result;

    for(u32 i = 0; i < 4; i++) {
        for(u32 j = 0; j < 4; j++) {
            result.matrix[i][j] = first.matrix[i][j] - second.matrix[i][j];
        }
    }

    return result;
}

theta_mat4x4f theta_mat4x4f_mul(theta_mat4x4f first, theta_mat4x4f second) {
    theta_mat4x4f result;

    for(u32 i = 0; i < 4; i++) {
        for(u32 j = 0; j < 4; j++) {
            result.matrix[i][j] = 0;

            for(u32 k = 0; k < 4; k++) {
                result.matrix[i][j] += first.matrix[i][k] * second.matrix[k][j];
            }
        }
    }

    return result;
}

theta_mat4x4f theta_mat4x4f_muls(theta_mat4x4f first, f32 scalar) {
    theta_mat4x4f result;

    for(u32 i = 0; i < 4; i++) {
        for(u32 j = 0; j < 4; j++) {
            result.matrix[i][j] = first.matrix[i][j] * scalar;
        }
    }

    return result;
}

theta_mat4x4f theta_mat4x4f_divs(theta_mat4x4f first, f32 scalar) {
    theta_mat4x4f result;

    if(scalar == 0.0f) {
        THETA_ERROR("theta_mat4x4f_divs has failed. The reason being, you cannot divide by a zero value. The scalar value provided to the method is zero.\n");
        return result;
    }

    for(u32 i = 0; i < 4; i++) {
        for(u32 j = 0; j < 4; j++) {
            result.matrix[i][j] = first.matrix[i][j] / scalar;
        }
    }

    return result;
}

theta_mat4x4f theta_mat4x4f_orthographic() {
    theta_mat4x4f result = theta_mat4x4f_identity();

    result.matrix[2][2] = 0.0f;

    return result;
}

theta_mat4x4f theta_mat4x4f_orthographic_args(f32 left, f32 right, f32 bottom, f32 top, f32 near, f32 far) {
    theta_mat4x4f result = {
        {
            {2.0f / (right-left), 0.0f, 0.0f, -((right + left) / (right-left))},
            {0.0f, 2.0f / (top-bottom), 0.0f, -((top+bottom)/(top-bottom))},
            {0.0f, 0.0f, (-2.0f)/(far-near), -((far+near)/(far-near))},
            {0.0f, 0.0f, 0.0f, 1.0f}
        }
    };

    return result;
}

theta_mat4x4f theta_mat4x4f_translate(theta_mat4x4f first, theta_vector3f vector) {
    theta_mat4x4f result = theta_mat4x4f_copy(first);

    result.matrix[3][0] += vector.x;
    result.matrix[3][1] += vector.y;
    result.matrix[3][2] += vector.z;

    return result;
}

theta_mat4x4f theta_mat4x4f_rotate(theta_mat4x4f first, theta_vector3f vector) {
    theta_mat4x4f x_component_rotation_matrix = {
        {
            {1.0f, 0.0f, 0.0f, 0.0f},
            {0.0f, cos(vector.x), -sin(vector.x), 0.0f},
            {0.0f, sin(vector.x), cos(vector.x), 0.0f},
            {0.0f, 0.0f, 0.0f, 1.0f}
        }
    };

    theta_mat4x4f y_component_rotation_matrix = {
        {
            {cos(vector.y), 0.0f, sin(vector.y), 0.0f},
            {0.0f, 1.0f, 0.0f, 0.0f},
            {-sin(vector.y), 0.0f, cos(vector.y), 0.0f},
            {0.0f, 0.0f, 0.0f, 1.0f}
        }
    };

    theta_mat4x4f z_component_rotation_matrix = {
        {
            {cos(vector.z), -sin(vector.z), 0.0f, 0.0f},
            {sin(vector.z), cos(vector.z), 0.0f, 0.0f},
            {0.0f, 0.0f, 1.0f, 0.0f},
            {0.0f, 0.0f, 0.0f, 1.0f}
        }
    };

    theta_mat4x4f complete_rotation_matrix = theta_mat4x4f_identity();
    complete_rotation_matrix = theta_mat4x4f_mul(complete_rotation_matrix, z_component_rotation_matrix);
    complete_rotation_matrix = theta_mat4x4f_mul(complete_rotation_matrix, y_component_rotation_matrix);
    complete_rotation_matrix = theta_mat4x4f_mul(complete_rotation_matrix, x_component_rotation_matrix);

    theta_mat4x4f result = theta_mat4x4f_copy(first);

    result = theta_mat4x4f_mul(result, complete_rotation_matrix);

    return result;
}

theta_mat4x4f theta_mat4x4f_scale(theta_mat4x4f first, theta_vector3f vector) {
    theta_mat4x4f result = theta_mat4x4f_copy(first);

    result.matrix[0][0] *= vector.x;
    result.matrix[1][1] *= vector.y;
    result.matrix[2][2] *= vector.z;

    return result;
}

theta_mat4x4f theta_mat4x4f_scales(theta_mat4x4f first, f32 scalar) {
    theta_mat4x4f result = theta_mat4x4f_copy(first);

    result.matrix[0][0] *= scalar;
    result.matrix[1][1] *= scalar;
    result.matrix[2][2] *= scalar;

    return result;
}

/*Honestly, this code is ripped from my previous engine, Impara2D, and I have no idea how this code works. I forgot.*/
theta_vector3f theta_mat4x4f_transform_vector(theta_mat4x4f matrix, theta_vector3f vector) {
    theta_vector3f result;

    float oldvector[4] = {vector.x, vector.y, vector.z, 1};

    float vector4[4] = {0, 0, 0, 0};

    for (int i = 0; i < 4; i++)
    {
        vector4[i] = oldvector[0] * matrix.matrix[0][i] + oldvector[1] * matrix.matrix[1][i] + oldvector[2] + matrix.matrix[2][i] + oldvector[3] * matrix.matrix[3][i];
    }

    result.x = vector4[0] / vector4[3];
    result.y = vector4[1] / vector4[3];
    result.z = vector4[2] / vector4[3];

    return result;
}