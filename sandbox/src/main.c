#include "../../theta/src/theta.h"

#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void sb_start() {
    theta_camera* camera = theta_camera_init(THETA_CAMERA_PROJECTION_TYPE_ORTHOGRAPHIC);

    theta_scene* scene = theta_scene_init(camera);

    theta_transform trsf;
    trsf.position = theta_vector3f_create_args(0.0f, 0.0f, 0.0f);
    trsf.rotation = theta_vector3f_create_args(0.0f, 0.0f, 0.0f);
    trsf.scale = theta_vector3f_create_args(1.0f, 1.0f, 1.0f);;
    theta_game_object* obj = theta_game_object_init(trsf, theta_renderable_init_quad("res/steve.png"));

    theta_scene_add_game_object(scene, obj);

    theta_scene_manager_set_active_scene(scene);
}

void sb_update(f64 elapsed_time) {
    theta_scene* scene = theta_scene_manager_get_active_scene();

    theta_game_object* obj = (theta_game_object*)theta_dynamic_list_get(&scene->game_objects, 0);

    obj->transform.rotation.y += 0.01f;
}

void sb_terminate() {
    
}

int main() {
    theta_application* sandbox;
    theta_application_descriptor descriptor;
    strcpy(descriptor.app_name, "Sandbox");
    descriptor.start = sb_start;
    descriptor.update = sb_update;
    descriptor.terminate = sb_terminate;
    descriptor.api = THETA_API_OPENGL;
    sandbox = theta_application_init(descriptor);
    theta_application_run(sandbox);
    theta_application_destruct(sandbox);
}