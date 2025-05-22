#pragma once

#include "core.h"
#include <cglm/cglm.h>
#include "transform.h"

typedef struct {
    theta_transform transform;
    mat4 projection_matrix;
}theta_camera;

/*
@brief Initializes a basic camera without any special parameters. Also initializes it at 0,0,0, with a rotation of 0,0,0, and a scale of 1,1,1.
@param type The type of camera to initialize. Can be orthographic or perspective.
*/
THETA_API void theta_camera_init(theta_camera* camera, mat4 projection);

THETA_API void theta_camera_get_view(theta_camera* camera, mat4 view);

THETA_API void theta_camera_get_forward_vector(theta_camera* camera, vec3 forward);