#include "../../theta/src/theta.h"

#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

theta_application* sandbox;

void on_walk(theta_vector3f axis) {
    theta_scene* scene = theta_scene_manager_get_active_scene();

    theta_game_object* o = theta_dynamic_list_get(&scene->game_objects, 0);

    o->transform.position.x += axis.x;
}

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

    /*Initialize input stuff*/
    theta_input_layout layout;
    layout.type = THETA_INPUT_LAYOUT_TYPE_KEYBOARD;
    layout.input_layout = INIT_STRUCT(theta_input_layout_keyboard);
    ((theta_input_layout_keyboard*)layout.input_layout)->positive = THETA_KEY_CODE_D;
    ((theta_input_layout_keyboard*)layout.input_layout)->negative = THETA_KEY_CODE_A;
    theta_input_system_bind_input(sandbox->input, "Walk", layout, &on_walk);
}

void sb_update(f64 elapsed_time) {
    theta_scene* scene = theta_scene_manager_get_active_scene();

    theta_game_object* obj = (theta_game_object*)theta_dynamic_list_get(&scene->game_objects, 0);

    //obj->transform.rotation.y += 5.0f * elapsed_time;
}

void sb_terminate() {
    
}

int main() {
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