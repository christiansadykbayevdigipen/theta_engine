#pragma once

#include "core.h"
#include "math/tmath.h"
#include "transform.h"

typedef struct {
    theta_transform transform;
    theta_mat4x4f projection_matrix;
}theta_camera;

/*
@brief Initializes a basic camera without any special parameters. Also initializes it at 0,0,0, with a rotation of 0,0,0, and a scale of 1,1,1.
@param type The type of camera to initialize. Can be orthographic or perspective.
*/
THETA_API theta_camera* theta_camera_init(theta_mat4x4f projection);

THETA_API theta_mat4x4f theta_camera_get_view(theta_camera* camera);

THETA_API void theta_camera_destroy(theta_camera* camera);