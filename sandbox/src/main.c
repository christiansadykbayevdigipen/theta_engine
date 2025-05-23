#include "../../theta/src/theta.h"

#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

theta_application sandbox;

#define PLAYER_WALKING_SPEED 5.0f
#define CAMERA_ROT_SPEED 5.0f

static f32 g_player_movement = 0.0f;
static f32 g_camera_rotation_movement = 0.0f;
static f32 g_camera_vertical_movement = 0.0f;
static f32 g_light_movement = 0.0f;
static f32 g_vertical_light_movement = 0.0f;

void on_walk(vec3 axis) {
    theta_scene* scene = theta_scene_manager_get_active_scene();

    theta_game_object o = scene->game_objects[0];

    g_player_movement = axis[0] * PLAYER_WALKING_SPEED;


    // if(axis.x > 0.0f) {
    //     o->transform.rotation.y = THETA_PI;
    // }
    // if(axis.x < 0.0f) {
    //     o->transform.rotation.y = 0;
    // }
}

void rotate_cam(vec3 axis) {
    g_camera_rotation_movement = axis[0] * CAMERA_ROT_SPEED;
}

void light_posf(vec3 axis) {
    g_light_movement = axis[0]* PLAYER_WALKING_SPEED;
}

void light_posv(vec3 axis) {
    g_vertical_light_movement = axis[0] * PLAYER_WALKING_SPEED;
}

void up_and_down(vec3 axis) {
    g_camera_vertical_movement = axis[0] * PLAYER_WALKING_SPEED;
}

void sb_start() {
    theta_camera camera;
    mat4 proj;
    glm_perspective(90, 16.0f/9.0f, 0.01f, 1000.0f, proj);
    theta_camera_init(&camera, proj);

    theta_scene* scene = theta_scene_init(camera);

    theta_transform trsf;
    vec3 pos = {0.0f, 0.0f, 0.0f};
    vec3 rot  = {0.0f, 0.0f, 0.0f};
    vec3 sca = {8.0f, 0.25f, 8.0f};

    glm_vec3_copy(pos, trsf.position);
    glm_vec3_copy(rot, trsf.rotation);
    glm_vec3_copy(sca, trsf.scale);
    
    theta_mesh mesh1;
    //theta_mesh_init_cube(&mesh1);
    theta_mesh_init_from_file(&mesh1, "res/thing.obj");

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
    theta_game_object_init(&obj, trsf, theta_renderable_init(mesh1, mat1, shader1), "Special");

    theta_scene_add_game_object(scene, obj);

    theta_light_descriptor light_point1;

    vec3 light_pos = {0.0f, 0.0f, 0.0f};
    vec3 light_rot = {0.0f, 0.0f, 0.0f};
    vec3 light_sca = {1.0f, 1.0f, 1.0f};
    vec3 ligh_col = {1.0f, 1.0f, 1.0f};

    glm_vec3_copy(light_pos, light_point1.transform.position);
    glm_vec3_copy(light_rot, light_point1.transform.rotation);
    glm_vec3_copy(light_sca, light_point1.transform.scale);
    glm_vec3_copy(ligh_col, light_point1.light_color);

    theta_light_ambient_descriptor ambience;
    ambience.ambient_strength = 0.1f;
    vec3 ambient_color = {1.0f, 1.0f, 1.0f};
    glm_vec3_copy(ambient_color, ambience.light_color);

    theta_scene_add_light(scene, light_point1);
    theta_scene_set_ambient_light(scene, ambience);

    theta_scene_manager_set_active_scene(scene);

    /*Initialize input stuff*/
    theta_input_layout layout;
    layout.type = THETA_INPUT_LAYOUT_TYPE_KEYBOARD;
    layout.input_layout = INIT_STRUCT(theta_input_layout_keyboard);
    ((theta_input_layout_keyboard*)layout.input_layout)->positive = THETA_KEY_CODE_W;
    ((theta_input_layout_keyboard*)layout.input_layout)->negative = THETA_KEY_CODE_S;
    theta_input_system_bind_input(sandbox.input, "Walk", layout, &on_walk);

    theta_input_layout new_layout;
    new_layout.type = THETA_INPUT_LAYOUT_TYPE_KEYBOARD;
    new_layout.input_layout = INIT_STRUCT(theta_input_layout_keyboard);
    ((theta_input_layout_keyboard*)new_layout.input_layout)->positive = THETA_KEY_CODE_D;
    ((theta_input_layout_keyboard*)new_layout.input_layout)->negative = THETA_KEY_CODE_A;
    theta_input_system_bind_input(sandbox.input, "RotateCam", new_layout, &rotate_cam);

    theta_input_layout up_n_down;
    up_n_down.type = THETA_INPUT_LAYOUT_TYPE_KEYBOARD;
    up_n_down.input_layout = INIT_STRUCT(theta_input_layout_keyboard);
    ((theta_input_layout_keyboard*)up_n_down.input_layout)->positive = THETA_KEY_CODE_Q;
    ((theta_input_layout_keyboard*)up_n_down.input_layout)->negative = THETA_KEY_CODE_E;
    theta_input_system_bind_input(sandbox.input, "UpNDown", up_n_down, &up_and_down);

    theta_input_layout new_new_layout;
    new_new_layout.type = THETA_INPUT_LAYOUT_TYPE_KEYBOARD;
    new_new_layout.input_layout = INIT_STRUCT(theta_input_layout_keyboard);
    ((theta_input_layout_keyboard*)new_new_layout.input_layout)->positive = THETA_KEY_CODE_LEFT;
    ((theta_input_layout_keyboard*)new_new_layout.input_layout)->negative = THETA_KEY_CODE_RIGHT;
    theta_input_system_bind_input(sandbox.input, "LightPos", new_new_layout, &light_posf);

    theta_input_layout new_new_new_layout;
    new_new_new_layout.type = THETA_INPUT_LAYOUT_TYPE_KEYBOARD;
    new_new_new_layout.input_layout = INIT_STRUCT(theta_input_layout_keyboard);
    ((theta_input_layout_keyboard*)new_new_new_layout.input_layout)->positive = THETA_KEY_CODE_UP;
    ((theta_input_layout_keyboard*)new_new_new_layout.input_layout)->negative = THETA_KEY_CODE_DOWN;
    theta_input_system_bind_input(sandbox.input, "LightPosSS", new_new_new_layout, &light_posv);
}

void sb_update(f64 elapsed_time) {
    theta_scene* scene = theta_scene_manager_get_active_scene();

    scene->lights[0].transform.position[2] += g_light_movement * elapsed_time;
    scene->lights[0].transform.position[1] += g_vertical_light_movement * elapsed_time;

    theta_camera* cam = &scene->bound_camera;

    theta_game_object* obj = &scene->game_objects[0];

    vec3 forward;
    theta_camera_get_forward_vector(cam, forward);
    vec3 dest;
    glm_vec3_scale(forward, g_player_movement * elapsed_time, dest);
    //glm_vec3_copy(dest, cam->transform.position);
    glm_vec3_add(cam->transform.position, dest, cam->transform.position);

    cam->transform.position[1] += g_camera_vertical_movement * elapsed_time;

    cam->transform.rotation[1] += g_camera_rotation_movement * elapsed_time;
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