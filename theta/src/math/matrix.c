#include "matrix.h"

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
            {0.0f, (2.0f / top-bottom), 0.0f, -((top+bottom)/(top-bottom))},
            {0.0f, 0.0f, (-2.0f)/(far-near), -((far+near)/(far-near))},
            {0.0f, 0.0f, 0.0f, 1.0f}
        }
    };

    return result;
}

theta_mat4x4f theta_mat4x4f_perspective() {
    theta_mat4x4f result = theta_mat4x4f_identity();

    return result;
}