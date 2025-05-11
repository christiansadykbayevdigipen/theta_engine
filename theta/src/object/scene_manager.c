#include "scene_manager.h"

static theta_scene* g_active_scene = NULL;

void theta_scene_manager_set_active_scene(theta_scene* scene) {
    THETA_PROFILE();
    
    g_active_scene = scene;
}

theta_scene* theta_scene_manager_get_active_scene() {
    return g_active_scene;
}