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
    THETA_CAMERA_PROJECT_TYPE_PERSPECTIVE
}theta_camera_projection_type;

THETA_API void theta_camera_init(theta_camera* camera, theta_camera_projection_type type);