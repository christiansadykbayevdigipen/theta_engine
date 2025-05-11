#pragma once

#include "core.h"
#include "object.h"
#include "camera.h"

typedef struct {
    theta_dynamic_list game_objects;
    theta_camera* bound_camera;
}theta_scene;

THETA_API void theta_scene_init(theta_scene* scene, theta_camera* camera);
THETA_API void theta_scene_add_game_object(theta_scene* scene, theta_game_object* game_object);

THETA_API void theta_scene_update(theta_scene* scene);
THETA_API void theta_scene_render(theta_scene* scene);