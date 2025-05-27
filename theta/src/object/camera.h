#pragma once

#include "core.h"
#include <cglm/cglm.h>
#include "transform.h"

typedef struct {
    theta_transform transform;
    mat4 projection_matrix;
}theta_camera;

// Initializes a camera with a specified projection matrix
THETA_API void theta_camera_init(theta_camera* camera, mat4 projection);

THETA_API void theta_camera_get_view(theta_camera* camera, mat4 view);

THETA_API void theta_camera_get_forward_vector(theta_camera* camera, vec3 forward);