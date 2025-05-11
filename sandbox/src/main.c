#include "../../theta/src/theta.h"

#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void sb_start() {
    theta_scene* scene = INIT_STRUCT(theta_scene);

    theta_camera* camera = INIT_STRUCT(theta_camera);
    theta_camera_init(camera, THETA_CAMERA_PROJECTION_TYPE_ORTHOGRAPHIC);

    theta_scene_init(scene, camera);

    theta_game_object* obj = INIT_STRUCT(theta_game_object);
    theta_transform trsf;
    trsf.position = theta_vector3f_create_args(0.0f, 0.0f, 0.0f);
    trsf.rotation = theta_vector3f_create_args(0.0f, 0.0f, 0.0f);
    trsf.scale = theta_vector3f_create_args(1.0f, 1.0f, 1.0f);
    theta_renderable* renderable = INIT_STRUCT(theta_renderable);
    theta_renderable_init_quad(renderable, "res/thingymabob.png");
    theta_game_object_init(obj, trsf, renderable);

    theta_scene_add_game_object(scene, obj);


    theta_scene_manager_set_active_scene(scene);
}

void sb_update(f64 elapsed_time) {
}

void sb_terminate() {
    
}

int main() {
    theta_application sandbox;
    theta_application_descriptor descriptor;
    strcpy(descriptor.app_name, "Sandbox");
    descriptor.start = sb_start;
    descriptor.update = sb_update;
    descriptor.terminate = sb_terminate;
    descriptor.api = THETA_API_OPENGL;
    theta_application_init(&sandbox, descriptor);
    theta_application_run(&sandbox);
    theta_application_destruct(&sandbox);
}