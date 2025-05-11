#include "camera.h"

void theta_camera_init(theta_camera* camera, theta_camera_projection_type type) {
    camera->transform.position = theta_vector3f_create();
    camera->transform.rotation = theta_vector3f_create();
    camera->transform.scale = theta_vector3f_create_args(1.0f, 1.0f, 1.0f);
    
    switch(type) {
    case THETA_CAMERA_PROJECT_TYPE_PERSPECTIVE: // TODO: Make this actually perspective
        camera->projection_matrix = theta_mat4x4f_orthographic();
        break;
    case THETA_CAMERA_PROJECTION_TYPE_ORTHOGRAPHIC:
        camera->projection_matrix = theta_mat4x4f_orthographic();
        break;
    default:
        THETA_WARN("theta_camera_init has a warning. The reason being, the projection type that was given to this method is not valid. Assuming orthographic projection.\n");
        camera->projection_matrix = theta_mat4x4f_orthographic();
        break;
    }
}

theta_mat4x4f theta_camera_get_view(theta_camera* camera) {
    theta_mat4x4f view_matrix = theta_mat4x4f_identity();

    view_matrix = theta_mat4x4f_scale(view_matrix, camera->transform.scale);
    view_matrix = theta_mat4x4f_rotate(view_matrix, camera->transform.rotation);
    view_matrix = theta_mat4x4f_translate(view_matrix, camera->transform.position);

    return view_matrix;
}

theta_mat4x4f theta_camera_get_projection(theta_camera* camera) {
    return camera->projection_matrix;
}