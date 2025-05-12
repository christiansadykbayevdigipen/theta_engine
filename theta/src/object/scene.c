#include "scene.h"

#include "renderer/renderer.h"

#include <memory.h>
#include <malloc.h>

theta_scene* theta_scene_init(theta_camera* camera) {
    THETA_PROFILE();

    theta_scene* scene = INIT_STRUCT(theta_scene);

    theta_dynamic_list_init(&scene->game_objects, sizeof(theta_game_object*));
    scene->bound_camera = camera;

    return scene;
}

void theta_scene_add_game_object(theta_scene* scene, theta_game_object* game_object) {
    THETA_PROFILE();
    theta_dynamic_list_push_back(&scene->game_objects, &game_object);
}

void theta_scene_update(theta_scene* scene) { // Update won't really do anything for now.
    for(u32 i = 0; i < scene->game_objects.length; i++) {
        //((theta_game_object*)scene->game_objects.elements[i])
    }
}

void theta_scene_render(theta_scene *scene) {
    // For each game object.
    for (u32 i = 0; i < scene->game_objects.length; i++) {
        theta_game_object* working_obj = (theta_game_object*)scene->game_objects.elements[i];
        
        // Check to see if it has a renderable. If not, theta_scene_render does not apply to this particular game object, so it should skip to the next game object in the list.
        if(!theta_game_object_has_component(working_obj, THETA_COMPONENT_TYPE_RENDERABLE)) {
            continue;
        }

        // Get the renderer off the game object
        theta_component rend_comp = theta_game_object_get_component(working_obj, THETA_COMPONENT_TYPE_RENDERABLE);
        theta_renderable* renderable = (theta_renderable*)rend_comp.data;

        // Set the Model, View, and Projection Matricies of the game object's renderer.
        theta_mat4x4f model = theta_game_object_get_model(working_obj);
        theta_mat4x4f view = theta_camera_get_view(scene->bound_camera);
        theta_mat4x4f proj = scene->bound_camera->projection_matrix;
        renderable->material.program.set_mvp(&renderable->material.program, model, view, proj);
        theta_renderer_submit(renderable);
    }
}