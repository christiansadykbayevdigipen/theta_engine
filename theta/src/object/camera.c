#include "camera.h"

#include <memory.h>
#include <malloc.h>

theta_camera* theta_camera_init(theta_mat4x4f projection) {
    THETA_PROFILE();

    theta_camera* camera = INIT_STRUCT(theta_camera);

    camera->transform.position = theta_vector3f_create();
    camera->transform.rotation = theta_vector3f_create();
    camera->transform.scale = theta_vector3f_create_args(1.0f, 1.0f, 1.0f);
    camera->projection_matrix = theta_mat4x4f_copy(projection);

    return camera;
}

theta_mat4x4f theta_camera_get_view(theta_camera* camera) {
    theta_mat4x4f view_matrix = theta_mat4x4f_identity();

    view_matrix = theta_mat4x4f_scale(view_matrix, camera->transform.scale);
    view_matrix = theta_mat4x4f_rotate(view_matrix, camera->transform.rotation);
    view_matrix = theta_mat4x4f_translate(view_matrix, camera->transform.position);

    return view_matrix;
}

void theta_camera_destroy(theta_camera* camera) {
    free(camera);
}