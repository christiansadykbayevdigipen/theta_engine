#include "camera.h"

#include <memory.h>
#include <malloc.h>

void theta_camera_init(theta_camera* camera, theta_mat4x4f projection) {
    THETA_PROFILE();

    camera->transform.position = theta_vector3f_create();
    camera->transform.rotation = theta_vector3f_create();
    camera->transform.scale = theta_vector3f_create_args(1.0f, 1.0f, 1.0f);
    camera->projection_matrix = theta_mat4x4f_copy(projection);
}

theta_mat4x4f theta_camera_get_view(theta_camera* camera) {
    theta_mat4x4f view_matrix = theta_mat4x4f_identity();

    view_matrix = theta_mat4x4f_scale(view_matrix, camera->transform.scale);
    view_matrix = theta_mat4x4f_rotate(view_matrix, camera->transform.rotation);
    view_matrix = theta_mat4x4f_translate(view_matrix, camera->transform.position);

    return view_matrix;
}