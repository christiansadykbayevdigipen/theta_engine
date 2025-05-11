#include "scene.h"

#include "renderer/renderer.h"

void theta_scene_init(theta_scene* scene, theta_camera* camera) {
    theta_dynamic_list_init(&scene->game_objects, sizeof(theta_game_object));
    scene->bound_camera = camera;
}

void theta_scene_add_game_object(theta_scene* scene, theta_game_object* game_object) {
    theta_dynamic_list_push_back(&scene->game_objects, game_object);
}

void theta_scene_update(theta_scene* scene) {
    for(u32 i = 0; i < scene->game_objects.length; i++) {
        //((theta_game_object*)scene->game_objects.elements[i])
    }
}

void theta_scene_render(theta_scene *scene) {
    for (u32 i = 0; i < scene->game_objects.length; i++) {
        theta_game_object* working_obj = (theta_game_object*)scene->game_objects.elements[i];
        
        if(!theta_game_object_has_component(working_obj, THETA_COMPONENT_TYPE_RENDERABLE)) {
            continue;
        }

        theta_component rend_comp = theta_game_object_get_component(working_obj, THETA_COMPONENT_TYPE_RENDERABLE);
        
        theta_renderable* renderable = (theta_renderable*)rend_comp.data;

        //renderable->material.program.set_mvp(&renderable->material.program, working_obj)
        //theta_renderer_submit(renderable);
    }
}