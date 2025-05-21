#include "../../theta/src/theta.h"

#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

theta_application sandbox;

#define PLAYER_WALKING_SPEED 2.0f * 100
#define CAMERA_ROT_SPEED 5.0f

static f32 g_player_movement = 0.0f;
static f32 g_camera_rotation_movement = 0.0f;
static f32 g_light_movement = 0.0f;

void on_walk(theta_vector3f axis) {
    theta_scene* scene = theta_scene_manager_get_active_scene();

    theta_game_object o = scene->game_objects[0];

    g_player_movement = axis.x * PLAYER_WALKING_SPEED;

    // if(axis.x > 0.0f) {
    //     o->transform.rotation.y = THETA_PI;
    // }
    // if(axis.x < 0.0f) {
    //     o->transform.rotation.y = 0;
    // }
}

void rotate_cam(theta_vector3f axis) {
    g_camera_rotation_movement = axis.x * CAMERA_ROT_SPEED;
}

void light_pos(theta_vector3f axis) {
    g_light_movement = axis.x * PLAYER_WALKING_SPEED;
}

void sb_start() {
    theta_camera camera;
    theta_camera_init(&camera, theta_mat4x4f_perspective_args(90, 1000000, 0.001f));

    theta_scene* scene = theta_scene_init(camera);
    

    theta_transform trsf;
    trsf.position = theta_vector3f_create_args(0.0f, 0.0f, 0.0f);
    trsf.rotation = theta_vector3f_create_args(0.0f, 0.0f, 0.0f);
    trsf.scale = theta_vector3f_create_args(1.0f, 1.0f, 1.0f);
    
    theta_mesh mesh1;
    //theta_mesh_init_cube(&mesh1);
    theta_mesh_init_from_file(&mesh1, "res/Sponza-master/sponza.obj");

    theta_material mat1;
    mat1.albedo = theta_texture_initw("res/quarter.jpeg", THETA_TEXTURE_WRAP_TYPE_REPEAT);
    mat1.lighted = TRUE;
    mat1.uses_albedo = TRUE;
    mat1.uses_color = FALSE;
    mat1.specular_strength = 0.5f;
    mat1.specular_highlight = 5;

    theta_shader_program shader1;
    theta_shader_program_init_type(&shader1, THETA_SHADER_TYPE_LIGHTING_SHADER_TEXTURED);

    theta_game_object obj;
    theta_game_object_init(&obj, trsf, theta_renderable_init(mesh1, mat1, shader1));

    theta_scene_add_game_object(scene, obj);

    theta_light_descriptor light_point1;
    light_point1.transform.position = theta_vector3f_create_args(0.0f, 3.0f, 0.0f);
    light_point1.transform.rotation = theta_vector3f_create();
    light_point1.transform.scale = theta_vector3f_create_args(1.0f, 1.0f, 1.0f);
    light_point1.light_color = theta_vector3f_create_args(1.0f, 1.0f, 1.0f);

    theta_light_ambient_descriptor ambience;
    ambience.ambient_strength = 0.1f;
    ambience.light_color = theta_vector3f_create_args(1.0f, 1.0f, 1.0f);

    theta_scene_add_light(scene, light_point1);
    theta_scene_set_ambient_light(scene, ambience);

    theta_scene_manager_set_active_scene(scene);

    /*Initialize input stuff*/
    theta_input_layout layout;
    layout.type = THETA_INPUT_LAYOUT_TYPE_KEYBOARD;
    layout.input_layout = INIT_STRUCT(theta_input_layout_keyboard);
    ((theta_input_layout_keyboard*)layout.input_layout)->positive = THETA_KEY_CODE_D;
    ((theta_input_layout_keyboard*)layout.input_layout)->negative = THETA_KEY_CODE_A;
    theta_input_system_bind_input(sandbox.input, "Walk", layout, &on_walk);

    theta_input_layout new_layout;
    new_layout.type = THETA_INPUT_LAYOUT_TYPE_KEYBOARD;
    new_layout.input_layout = INIT_STRUCT(theta_input_layout_keyboard);
    ((theta_input_layout_keyboard*)new_layout.input_layout)->positive = THETA_KEY_CODE_C;
    ((theta_input_layout_keyboard*)new_layout.input_layout)->negative = THETA_KEY_CODE_Z;
    theta_input_system_bind_input(sandbox.input, "RotateCam", new_layout, &rotate_cam);

    theta_input_layout new_new_layout;
    new_new_layout.type = THETA_INPUT_LAYOUT_TYPE_KEYBOARD;
    new_new_layout.input_layout = INIT_STRUCT(theta_input_layout_keyboard);
    ((theta_input_layout_keyboard*)new_new_layout.input_layout)->positive = THETA_KEY_CODE_LEFT;
    ((theta_input_layout_keyboard*)new_new_layout.input_layout)->negative = THETA_KEY_CODE_RIGHT;
    theta_input_system_bind_input(sandbox.input, "LightPos", new_new_layout, &light_pos);
}

void sb_update(f64 elapsed_time) {
    theta_scene* scene = theta_scene_manager_get_active_scene();

    scene->lights[0].transform.position.x += g_light_movement * elapsed_time;

    theta_camera* cam = &scene->bound_camera;

    theta_game_object* obj = &scene->game_objects[0];

    cam->transform.position.z -= g_player_movement * elapsed_time;
    cam->transform.rotation.y -= g_camera_rotation_movement * elapsed_time;
    //obj->transform.rotation.y += 1.5f * elapsed_time;
    //obj->transform.rotation.x += 1.5f * elapsed_time;
    //obj1->transform.rotation.y -= 1.5f * elapsed_time;
    //obj1->transform.rotation.x -= 1.5f * elapsed_time;
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
    theta_application_init(&sandbox, descriptor);
    theta_application_run(&sandbox);
    theta_application_destruct(&sandbox);
}