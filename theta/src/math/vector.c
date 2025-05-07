#include "vector.h"

theta_vector3f theta_vector3f_create() {
    theta_vector3f vector;
    vector.x = 0.0f;
    vector.y = 0.0f;
    vector.z = 0.0f;

    return vector;
}

theta_vector3f theta_vector3f_create_args(f32 x, f32 y, f32 z) {
    theta_vector3f vector;
    vector.x = x;
    vector.y = y;
    vector.z = z;
    
    return vector;
}

theta_vector3f theta_vector3f_add(theta_vector3f first, theta_vector3f second) {
    theta_vector3f result;
    result.x = first.x + second.x;
    result.y = first.y + second.y;
    result.z = first.z + second.z;

    return result;
}

theta_vector3f theta_vector3f_sub(theta_vector3f first, theta_vector3f second) {
    theta_vector3f result;
    result.x = first.x - second.x;
    result.y = first.y - second.y;
    result.z = first.z - second.z;

    return result;
}

theta_vector3f theta_vector3f_mul(theta_vector3f first, theta_vector3f second) {
    theta_vector3f result;
    result.x = first.x * second.x;
    result.y = first.y * second.y;
    result.z = first.z * second.z;

    return result;
}

theta_vector3f theta_vector3f_muls(theta_vector3f first, f32 scalar) {
    theta_vector3f result;
    result.x = first.x * scalar;
    result.y = first.y * scalar;
    result.z = first.z * scalar;

    return result;
}

theta_vector3f theta_vector3f_div(theta_vector3f first, theta_vector3f second) {
    theta_vector3f result;
    result.x = first.x / second.x;
    result.y = first.y / second.y;
    result.z = first.z / second.z;

    return result;
}

theta_vector3f theta_vector3f_divs(theta_vector3f first, f32 scalar) {
    theta_vector3f result;
    result.x = first.x / scalar;
    result.y = first.y / scalar;
    result.z = first.z / scalar;

    return result;
}