#pragma once

#include "core.h"
#include "scene.h"

// This will bind a scene to the scene manager.
THETA_API void theta_scene_manager_set_active_scene(theta_scene* scene);

// This will return NULL if there is no active scene bound.
THETA_API theta_scene* theta_scene_manager_get_active_scene();

// Destroys the current associated scene and deallocates the scene manager.
THETA_API void theta_scene_manager_destroy();