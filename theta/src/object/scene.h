#pragma once

#include "core.h"
#include "object.h"
#include "camera.h"
#include "light.h"
#include "renderer/skybox.h"

#define MAX_LIGHTS 99

typedef struct {
    theta_game_object* game_objects;
    theta_camera bound_camera;
    theta_light lights[MAX_LIGHTS];
    u32 light_count;
}theta_scene;

// Initializes a blank scene with a camera.
THETA_API theta_scene* theta_scene_init(theta_camera camera);

// Adds a game object to the stack of game objects in the scene. There is no maximum limit of game objects.
THETA_API void theta_scene_add_game_object(theta_scene* scene, theta_game_object game_object);

// Returns the bound camera of the scene.
THETA_API theta_camera* theta_scene_get_bound_camera(theta_scene* scene);

// Gets a game object by index of the theta_scene::game_objects dynamic array. If it is out of bounds, this will return NULL.
THETA_API theta_game_object* theta_scene_get_game_object(theta_scene* scene, u32 index);

// Gets a game object by the identifier.
THETA_API theta_game_object* theta_scene_get_game_object_by_tag(theta_scene* scene, const char* tag);

THETA_API u32 theta_scene_get_game_object_count(theta_scene* scene);

THETA_API theta_game_object* theta_scene_get_game_objects(theta_scene* scene);

THETA_API u32 theta_scene_get_index_by_game_object(theta_scene* scene, theta_game_object* object);

THETA_API void theta_scene_remove_game_object(theta_scene* scene, theta_game_object* object);

THETA_API void theta_scene_remove_game_object_by_index(theta_scene* scene, u32 index);

// Adds a light to the light stack in the scene. There is a maximum of MAX_LIGHTS that is permitted per scene.
THETA_API void theta_scene_add_light(theta_scene* scene, theta_light light);

// Adds a skybox to a particular scene.
THETA_API void theta_scene_give_skybox(theta_scene* scene, theta_skybox skybox);

// Updates all game objects and behaviours associated with each game object
THETA_API void theta_scene_update(theta_scene* scene);

// Submits all renderables on the game object stack.
THETA_API void theta_scene_render(theta_scene* scene);

// Deallocates all of the memory allocated by the scene
// Beware: This will cause scene to become a dangling pointer, since it is freeing itself. This is because scene is always a heap allocated structure.
THETA_API void theta_scene_destroy(theta_scene* scene);