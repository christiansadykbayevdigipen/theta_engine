#include "scene.h"

#include "renderer/renderer.h"

#include <memory.h>
#include <malloc.h>

#include "stb_ds.h"

theta_scene* theta_scene_init(theta_camera camera) {
    THETA_PROFILE();

    theta_scene* scene = INIT_STRUCT(theta_scene);

    scene->bound_camera = camera;
    scene->ambient_lighting_set = FALSE;
    scene->lights = NULL;
    scene->game_objects = NULL;

    return scene;
}

void theta_scene_add_game_object(theta_scene* scene, theta_game_object game_object) {
    THETA_PROFILE();
    
    for(u32 i = 0; i < arrlen(scene->game_objects); i++) {
        if(strcmp(scene->game_objects[i].identifier, game_object.identifier) == 0) {
            THETA_ERROR("theta_scene_add_game_object has failed. The reason being, you are trying to add a game object with an identifier that already exists in the scene!\n");
            return;
        }
    }

    arrput(scene->game_objects, game_object);
}

void theta_scene_add_light(theta_scene* scene, theta_light_descriptor light_point) {
    THETA_PROFILE();
    
    arrpush(scene->lights, light_point);
}

void theta_scene_update(theta_scene* scene) { // Update won't really do anything for now.
    for(u32 i = 0; i < arrlen(scene->game_objects); i++) {
        //((theta_game_object*)scene->game_objects.elements[i])
    }
}

void theta_scene_render(theta_scene *scene) {
    // For each game object.
    for (u32 i = 0; i < arrlen(scene->game_objects); i++) {
        theta_game_object working_obj = scene->game_objects[i];
        
        // Check to see if it has a renderable. If not, theta_scene_render does not apply to this particular game object, so it should skip to the next game object in the list.
        if(!theta_game_object_has_component(&working_obj, THETA_COMPONENT_TYPE_RENDERABLE)) {
            continue;
        }

        // Get the renderer off the game object
        theta_component rend_comp = theta_game_object_get_component(&working_obj, THETA_COMPONENT_TYPE_RENDERABLE);
        theta_renderable* renderable = (theta_renderable*)rend_comp.data;

        // Set the Model, View, and Projection Matricies of the game object's renderer.
        theta_mat4x4f model = theta_game_object_get_model(&working_obj);
        theta_mat4x4f view = theta_camera_get_view(&scene->bound_camera);
        theta_mat4x4f proj = scene->bound_camera.projection_matrix;
        //renderable->program.set_light_position(&renderable->program, scene_light.transform.position);
        renderable->program.set_mvp(&renderable->program, model, view, proj);

        if(renderable->material.lighted) {
            if(arrlen(scene->lights) > 0) { // Just use the first light source in the lights list. We don't have multiple light source capability yet.
                theta_light_descriptor* light_src = &scene->lights[0];
                renderable->program.set_light(&renderable->program, *light_src, scene->bound_camera.transform.position);
                renderable->program.set_ambient_light(&renderable->program, scene->ambient_lighting);
            }
        }

        theta_renderer_submit(renderable);
    }
}

void theta_scene_set_ambient_light(theta_scene* scene, theta_light_ambient_descriptor ambient_lighting) {
    scene->ambient_lighting_set = TRUE;
    scene->ambient_lighting = ambient_lighting;
}

theta_camera* theta_scene_get_bound_camera(theta_scene* scene) {
    return &scene->bound_camera;
}

theta_game_object* theta_scene_get_game_object(theta_scene* scene, u32 index) {
    if(index < 0 || index > arrlen(scene->game_objects)) {
        THETA_ERROR("theta_scene_get_game_object has failed. The reason being, the index is out of range!\n");
        return NULL;
    }

    return &scene->game_objects[index];
}

theta_game_object* theta_scene_get_game_object_by_tag(theta_scene* scene, const char* tag) {
    BOOL found_obj = FALSE;
    theta_game_object* object = NULL;
    
    for(u32 i = 0; i < arrlen(scene->game_objects); i++) {
        if(strcmp(scene->game_objects[i].identifier, tag) == 0) {
            found_obj = TRUE;
            object = &scene->game_objects[i];
        }
    }

    if(!found_obj) {
        THETA_ERROR("theta_scene_get_game_object has failed. The reason being, the identifier supplied did not match any game objects in the scene's game object list!\n");
        return NULL;
    }

    return object;
}