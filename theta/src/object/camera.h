#pragma once

#include "core.h"
#include "math/tmath.h"
#include "transform.h"

typedef struct {
    theta_transform transform;
    theta_mat4x4f projection_matrix;
}theta_camera;

typedef enum {
    THETA_CAMERA_PROJECTION_TYPE_ORTHOGRAPHIC,
    THETA_CAMERA_PROJECTION_TYPE_PERSPECTIVE
}theta_camera_projection_type;

/*
@brief Initializes a basic camera without any special parameters. Also initializes it at 0,0,0, with a rotation of 0,0,0, and a scale of 1,1,1.
@param type The type of camera to initialize. Can be orthographic or perspective.
*/
THETA_API theta_camera* theta_camera_init(theta_camera_projection_type type);

THETA_API theta_mat4x4f theta_camera_get_view(theta_camera* camera);

THETA_API void theta_camera_destroy(theta_camera* camera);