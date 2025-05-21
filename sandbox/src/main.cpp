#include "../../theta/src/theta.h"

#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// theta_application* sandbox;

#define PLAYER_WALKING_SPEED 2.0f

static f32 g_PlayerMovement = 0.0f;

void on_walk(theta_vector3f axis) {
    theta_scene* scene = theta_scene_manager_get_active_scene();
    theta_game_object* o = (theta_game_object*)theta_dynamic_list_get(&scene->game_objects, 0);
    g_PlayerMovement = axis.x * PLAYER_WALKING_SPEED;
    // if(axis.x > 0.0f) {
    //     o->transform.rotation.y = THETA_PI;
    // }
    // if(axis.x < 0.0f) {
    //     o->transform.rotation.y = 0;
    // }
}

// void sb_start() {
//     theta_camera* camera = theta_camera_init(theta_mat4x4f_perspective_args(90, 1000, 0.01f));

//     theta_scene* scene = theta_scene_init(camera);
//     camera->transform.rotation.x += 1.0f/3.0f*THETA_PI;
    

//     theta_transform trsf;
//     trsf.position = theta_vector3f_create_args(0.0f, 0.0f, 0.0f);
//     trsf.rotation = theta_vector3f_create_args(0.0f, 0.0f, 0.0f);
//     trsf.scale = theta_vector3f_create_args(1.0f, 1.0f, 1.0f);
    
//     theta_mesh mesh1;
//     //theta_mesh_init_cube(&mesh1);
//     theta_mesh_init_from_file(&mesh1, "res/thing.obj");

//     theta_material mat1;
//     mat1.albedo = theta_texture_initw("res/quarter.jpeg", THETA_TEXTURE_WRAP_TYPE_REPEAT);
//     mat1.lighted = TRUE;
//     mat1.uses_albedo = TRUE;
//     mat1.uses_color = FALSE;
//     mat1.specular_strength = 0.5f;
//     mat1.specular_highlight = 5;

//     theta_shader_program shader1;
//     theta_shader_program_init_type(&shader1, THETA_SHADER_TYPE_LIGHTING_SHADER_TEXTURED);

//     theta_game_object* obj = theta_game_object_init(trsf, theta_renderable_init(mesh1, mat1, shader1));

//     theta_scene_add_game_object(scene, obj);

//     theta_light_descriptor light_point1;
//     light_point1.transform.position = theta_vector3f_create_args(5.0f, 3.0f, 0.0f);
//     light_point1.transform.rotation = theta_vector3f_create();
//     light_point1.transform.scale = theta_vector3f_create_args(1.0f, 1.0f, 1.0f);
//     light_point1.light_color = theta_vector3f_create_args(1.0f, 1.0f, 1.0f);

//     theta_light_ambient_descriptor ambience;
//     ambience.ambient_strength = 0.1f;
//     ambience.light_color = theta_vector3f_create_args(1.0f, 1.0f, 1.0f);

//     theta_scene_add_light(scene, light_point1);
//     theta_scene_set_ambient_light(scene, ambience);

//     theta_scene_manager_set_active_scene(scene);

//     /*Initialize input stuff*/
//     theta_input_layout layout;
//     layout.type = THETA_INPUT_LAYOUT_TYPE_KEYBOARD;
//     layout.input_layout = INIT_STRUCT(theta_input_layout_keyboard);
//     ((theta_input_layout_keyboard*)layout.input_layout)->positive = THETA_KEY_CODE_D;
//     ((theta_input_layout_keyboard*)layout.input_layout)->negative = THETA_KEY_CODE_A;
//     theta_input_system_bind_input(sandbox->input, "Walk", layout, &on_walk);
// }

// void sb_update(f64 elapsed_time) {
//     theta_scene* scene = theta_scene_manager_get_active_scene();

//     theta_game_object* obj = (theta_game_object*)theta_dynamic_list_get(&scene->game_objects, 0);
//     //theta_game_object* obj1 = (theta_game_object*)theta_dynamic_list_get(&scene->game_objects, 1);
//     theta_camera* cam = scene->bound_camera;

//     cam->transform.position.z += g_player_movement * elapsed_time;
//     obj->transform.rotation.y += 1.5f * elapsed_time;
//     obj->transform.rotation.x += 1.5f * elapsed_time;
//     //obj1->transform.rotation.y -= 1.5f * elapsed_time;
//     //obj1->transform.rotation.x -= 1.5f * elapsed_time;
// }

// void sb_terminate() {
    
// }

// int main() {
//     theta_application_descriptor descriptor;
//     strcpy(descriptor.app_name, "Sandbox");
//     descriptor.start = sb_start;
//     descriptor.update = sb_update;
//     descriptor.terminate = sb_terminate;
//     descriptor.api = THETA_API_OPENGL;
//     sandbox = theta_application_init(descriptor);
//     theta_application_run(sandbox);
//     theta_application_destruct(sandbox);
// }

theta::ApplicationDescriptor g_Properties = {1280, 720, "Sandbox", THETA_API_OPENGL};

class Sandbox : public theta::Application
{
public:
    Sandbox():
        theta::Application(g_Properties)
    {

    }

    virtual void Start() override
    {
        theta_camera *camera = theta_camera_init(theta_mat4x4f_perspective_args(90, 1000, 0.01f));
        theta_scene *scene = theta_scene_init(camera);
        camera->transform.rotation.x += 1.0f / 3.0f * THETA_PI;

        theta_transform trsf;
        trsf.position = theta_vector3f_create_args(0.0f, 0.0f, 0.0f);
        trsf.rotation = theta_vector3f_create_args(0.0f, 0.0f, 0.0f);
        trsf.scale = theta_vector3f_create_args(1.0f, 1.0f, 1.0f);

        theta_mesh mesh1;
        // theta_mesh_init_cube(&mesh1);
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
        theta_game_object *obj = theta_game_object_init(trsf, theta_renderable_init(mesh1, mat1, shader1));
        theta_scene_add_game_object(scene, obj);
        theta_light_descriptor light_point1;
        light_point1.transform.position = theta_vector3f_create_args(5.0f, 3.0f, 0.0f);
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
        ((theta_input_layout_keyboard *)layout.input_layout)->positive = THETA_KEY_CODE_D;
        ((theta_input_layout_keyboard *)layout.input_layout)->negative = THETA_KEY_CODE_A;
        theta_input_system_bind_input(GetInput(), "Walk", layout, &on_walk);
    }

    virtual void Update(f64 elapsedMs) override
    {
     theta_scene* scene = theta_scene_manager_get_active_scene();
     theta_game_object* obj = (theta_game_object*)theta_dynamic_list_get(&scene->game_objects, 0);
     //theta_game_object* obj1 = (theta_game_object*)theta_dynamic_list_get(&scene->game_objects, 1);
     theta_camera* cam = scene->bound_camera;
     cam->transform.position.z += g_PlayerMovement * elapsedMs;
     obj->transform.rotation.y += 1.5f * elapsedMs;
     obj->transform.rotation.x += 1.5f * elapsedMs;
     //obj1->transform.rotation.y -= 1.5f * elapsed_time;
     //obj1->transform.rotation.x -= 1.5f * elapsed_time;
    }

    virtual void Terminate() override
    {

    }
};

int main() 
{
    Sandbox app;
    app.Run();
}