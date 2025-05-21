#pragma once

#include "core.h"
#include "object.h"
#include "camera.h"
#include "light.h"

#include "stb_ds.h"

typedef struct {
    theta_game_object* game_objects;
    theta_light_descriptor* lights;
    theta_camera bound_camera;

    BOOL ambient_lighting_set;
    theta_light_ambient_descriptor ambient_lighting;
}theta_scene;

THETA_API theta_scene* theta_scene_init(theta_camera camera);
THETA_API void theta_scene_add_game_object(theta_scene* scene, theta_game_object game_object);
THETA_API void theta_scene_add_light(theta_scene* scene, theta_light_descriptor light_point);
THETA_API void theta_scene_set_ambient_light(theta_scene* scene, theta_light_ambient_descriptor ambient_lighting);

THETA_API void theta_scene_update(theta_scene* scene);
THETA_API void theta_scene_render(theta_scene* scene);