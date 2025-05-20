#pragma once

#include "core.h"
#include "scene.h"

THETA_API void theta_scene_manager_set_active_scene(theta_scene* scene);
THETA_API theta_scene* theta_scene_manager_get_active_scene();

THETA_API void theta_scene_manager_destroy();