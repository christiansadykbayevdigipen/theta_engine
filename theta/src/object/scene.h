#pragma once

#include "core.h"
#include "object.h"
#include "camera.h"
#include "light.h"
#include "renderer/skybox.h"

#include "stb_ds.h"

#define MAX_LIGHTS 90

typedef struct {
    theta_game_object* game_objects;
    theta_camera bound_camera;
    theta_light lights[MAX_LIGHTS];
    u32 light_count;
}theta_scene;

THETA_API theta_scene* theta_scene_init(theta_camera camera);
THETA_API void theta_scene_add_game_object(theta_scene* scene, theta_game_object game_object);
THETA_API theta_camera* theta_scene_get_bound_camera(theta_scene* scene);
THETA_API theta_game_object* theta_scene_get_game_object(theta_scene* scene, u32 index);
THETA_API theta_game_object* theta_scene_get_game_object_by_tag(theta_scene* scene, const char* tag);
THETA_API void theta_scene_add_light(theta_scene* scene, theta_light light);
THETA_API void theta_scene_give_skybox(theta_scene* scene, theta_skybox skybox);

THETA_API void theta_scene_update(theta_scene* scene);
THETA_API void theta_scene_render(theta_scene* scene);