#include "camera.h"

#include <memory.h>
#include <malloc.h>

void theta_camera_init(theta_camera* camera, mat4 projection) {
    THETA_PROFILE();

    vec3 pos = {0.0f, 0.0f, 0.0f};
    vec3 rot = {0.0f, 0.0f, 0.0f};
    vec3 sca = {1.0f, 1.0f, 1.0f};

    glm_vec3_copy(pos, camera->transform.position);
    glm_vec3_copy(rot, camera->transform.rotation);
    glm_vec3_copy(sca, camera->transform.scale);
    glm_mat4_copy(projection, camera->projection_matrix);
}

void theta_camera_get_view(theta_camera* camera, mat4 view) {
    mat4 view_matrix;
    glm_mat4_identity(view_matrix);

    glm_scale(view_matrix, camera->transform.scale);
    //glm_rotate(view_matrix, camera->transform.rotation);
    vec3 normalized;
    glm_vec3_copy(camera->transform.rotation, normalized); glm_normalize(normalized);
    f32 norm = glm_vec3_norm(camera->transform.rotation);
    glm_rotate(view_matrix, norm, normalized);
    glm_translate(view_matrix, camera->transform.position);

    glm_mat4_copy(view_matrix, view);
}

void theta_camera_get_forward_vector(theta_camera* camera, vec3 forward) {
    mat4 view;
    theta_camera_get_view(camera, view);

    vec3 temp_forward = {view[0][2], view[1][2], view[2][2]};
    glm_normalize(temp_forward);

    glm_vec3_copy(temp_forward, forward);
}