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
static vec3 g_rotating = {0.0f, 0.0f, 0.0f};
static f32 g_vertical_look;

void on_walk(vec3 axis) {
    theta_scene* scene = theta_scene_manager_get_active_scene();

    g_player_movement = axis[0] * PLAYER_WALKING_SPEED;
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

void vertically_look(vec3 axis) {
    g_vertical_look = axis[0] * CAMERA_ROT_SPEED;
}

void reset_thing(vec3 axis) {
    if(axis[0] > 0.0f) {
        theta_scene* scene = theta_scene_manager_get_active_scene();
        scene->bound_camera.transform.rotation[0] = 0.0f;
        scene->bound_camera.transform.rotation[1] = 0.0f;
        scene->bound_camera.transform.rotation[2] = 0.0f;
    }
}

void make_a_bunch_of_thingies(theta_scene* scene) {
    for(u32 i = 0; i < 0; i++) {
        theta_transform trsf2;
        vec3 pos2 = {5.0f + (i*8), 8.0f, 0.0f};
        vec3 rot2 = {0.0f, 0.0f, 0.0f};
        vec3 sca2 = {1.0f, 1.0f, 1.0f};

        glm_vec3_copy(pos2, trsf2.position);
        glm_vec3_copy(rot2, trsf2.rotation);
        glm_vec3_copy(sca2, trsf2.scale);

        theta_mesh mesh2;
        theta_mesh_init_from_file(&mesh2, "res/thing.obj");

        theta_material mat2;
        mat2.lighted = TRUE;
        mat2.uses_color = FALSE;
        mat2.is_skybox = FALSE;
        mat2.texture_tiling_x = 6;
        mat2.texture_tiling_y = 6;
        mat2.albedo = theta_texture_initw("res/Rock062_2K-JPG/Rock062_2K-JPG_Color.jpg", THETA_TEXTURE_WRAP_TYPE_REPEAT);
        mat2.normal_map = theta_texture_initw("res/Rock062_2K-JPG/Rock062_2K-JPG_NormalGL.jpg", THETA_TEXTURE_WRAP_TYPE_REPEAT);
        mat2.metallic_map = NULL;
        mat2.metallic = 0.5f;
        mat2.roughness_map = theta_texture_initw("res/Rock062_2K-JPG/Rock062_2K-JPG_Roughness.jpg", THETA_TEXTURE_WRAP_TYPE_REPEAT);
        mat2.ao_map = theta_texture_initw("res/Rock062_2K-JPG/Rock062_2K-JPG_AmbientOcclusion.jpg", THETA_TEXTURE_WRAP_TYPE_REPEAT);

        theta_shader_program shader2;
        theta_shader_program_init_type(&shader2, THETA_SHADER_TYPE_LIGHTING_SHADER_TEXTURED);

        char name[800];
        sprintf(name, "Special%d", i);

        theta_game_object obj2;
        theta_game_object_init(&obj2, trsf2, theta_renderable_init(mesh2, mat2, shader2), name);

        theta_scene_add_game_object(scene, obj2);
    }
}

void sb_start(theta_application* app) {
    theta_camera camera;
    mat4 proj;
    glm_perspective(glm_rad(90), 16.0f/9.0f, 0.01f, 1000.0f, proj);
    theta_camera_init(&camera, proj);

    theta_scene* scene = theta_scene_init(camera);

    theta_transform trsf2;
    vec3 pos2 = {0.0f, 4.0f, 0.0f};
    vec3 rot2  = {0.0f, 0.0f, 0.0f};
    vec3 sca2 = {8.0f, 0.15f, 8.0f};
    //vec3 sca2 = {1.0f, 1.0f, 1.0f};

    glm_vec3_copy(pos2, trsf2.position);
    glm_vec3_copy(rot2, trsf2.rotation);
    glm_vec3_copy(sca2, trsf2.scale);
    
    theta_mesh mesh2;
    theta_mesh_init_from_file(&mesh2, "res/thing.obj");

    theta_material mat2;
    mat2.lighted = TRUE;
    mat2.uses_color = FALSE;
    mat2.is_skybox = FALSE;
    mat2.texture_tiling_x = 6;
    mat2.texture_tiling_y = 6;
    mat2.albedo = theta_texture_initw("res/Rock062_2K-JPG/Rock062_2K-JPG_Color.jpg", THETA_TEXTURE_WRAP_TYPE_REPEAT);
    mat2.normal_map = theta_texture_initw("res/Rock062_2K-JPG/Rock062_2K-JPG_NormalGL.jpg", THETA_TEXTURE_WRAP_TYPE_REPEAT);
    mat2.roughness_map = theta_texture_initw("res/Rock062_2K-JPG/Rock062_2K-JPG_Roughness.jpg", THETA_TEXTURE_WRAP_TYPE_REPEAT);
    mat2.ao_map = theta_texture_initw("res/Rock062_2K-JPG/Rock062_2K-JPG_AmbientOcclusion.jpg", THETA_TEXTURE_WRAP_TYPE_REPEAT);
    mat2.metallic_map = NULL;
    mat2.metallic = 0.5f;

    theta_shader_program shader2;
    theta_shader_program_init_type(&shader2, THETA_SHADER_TYPE_LIGHTING_SHADER_TEXTURED);

    theta_game_object obj2;
    theta_game_object_init(&obj2, trsf2, theta_renderable_init(mesh2, mat2, shader2), "Special2");

    theta_scene_add_game_object(scene, obj2);

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

    theta_input_layout look_vertically;
    look_vertically.type = THETA_INPUT_LAYOUT_TYPE_KEYBOARD;
    look_vertically.input_layout = INIT_STRUCT(theta_input_layout_keyboard);
    ((theta_input_layout_keyboard*)look_vertically.input_layout)->positive = THETA_KEY_CODE_Z;
    ((theta_input_layout_keyboard*)look_vertically.input_layout)->negative = THETA_KEY_CODE_C;
    theta_input_system_bind_input(sandbox.input, "LookVertically", look_vertically, &vertically_look);

    theta_input_layout reset;
    reset.type = THETA_INPUT_LAYOUT_TYPE_KEYBOARD;
    reset.input_layout = INIT_STRUCT(theta_input_layout_keyboard);
    ((theta_input_layout_keyboard*)reset.input_layout)->positive = THETA_KEY_CODE_R;
    ((theta_input_layout_keyboard*)reset.input_layout)->negative = THETA_KEY_CODE_T;
    theta_input_system_bind_input(sandbox.input, "Reset", reset, &reset_thing);

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

    char texture_locations[6][MAX_STRING] = 
    {
        "res/right.jpg",
        "res/left.jpg",
        "res/top.jpg",
        "res/bottom.jpg",
        "res/front.jpg",
        "res/back.jpg",
    };
    //  char texture_locations[6][MAX_STRING] = 
    //  {
    //      "res/lightblue/right.png",
    //      "res/lightblue/left.png",
    //      "res/lightblue/top.png",
    //      "res/lightblue/bot.png",
    //      "res/lightblue/front.png",
    //      "res/lightblue/back.png",
    //  };

    theta_skybox skybox;
    theta_skybox_init(&skybox, texture_locations);

    theta_scene_give_skybox(scene, skybox);

    // Give the scene a light source
    theta_light light;
    vec3 light_color = {1.0f, 1.0f, 1.0f};
    vec3 light_location = {1.0f, 4.5f, 0.0f};
    light.intensity = 50;
    glm_vec3_copy(light_color, light.color);
    glm_vec3_copy(light_location, light.location);
    theta_scene_add_light(scene, light);
    make_a_bunch_of_thingies(scene);
}

void sb_update(theta_application* app, f64 elapsed_time) {
    theta_scene* scene = theta_scene_manager_get_active_scene();

    theta_camera* cam = &scene->bound_camera;

    theta_game_object* obj = &scene->game_objects[0];

    vec3 forward;
    theta_camera_get_forward_vector(cam, forward);
    vec3 dest;
    glm_vec3_scale(forward, g_player_movement * elapsed_time, dest);
    glm_vec3_add(cam->transform.position, dest, cam->transform.position);

    cam->transform.position[1] += g_camera_vertical_movement * elapsed_time;
    cam->transform.rotation[1] += g_camera_rotation_movement * elapsed_time;
    cam->transform.rotation[0] += g_vertical_look * elapsed_time;

    scene->lights[0].location[0] += g_light_movement * elapsed_time;
    scene->lights[0].location[1] += g_vertical_light_movement * elapsed_time;
}

void sb_terminate(theta_application* app) {
    
}

int main() {
    theta_application_descriptor descriptor;
    strcpy(descriptor.app_name, "Sandbox");
    descriptor.start = sb_start;
    descriptor.update = sb_update;
    descriptor.terminate = sb_terminate;
    descriptor.api = THETA_API_OPENGL;
    descriptor.starts_in_fullscreen = FALSE;
    descriptor.cursor_lock = FALSE;
    descriptor.enable_imgui = FALSE;
    theta_application_init(&sandbox, descriptor);
    theta_application_run(&sandbox);
    theta_application_destruct(&sandbox);
}