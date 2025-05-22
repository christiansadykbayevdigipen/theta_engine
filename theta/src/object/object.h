#pragma once

#include "core.h"

#include "renderer/renderable.h"
#include <cglm/cglm.h>
#include "transform.h"

#define MAX_COMPONENTS 30

typedef enum {
    THETA_COMPONENT_TYPE_RENDERABLE
}theta_component_type;

typedef struct {
    void* data;
    theta_component_type type;
}theta_component;

typedef struct {
    theta_transform transform;
    theta_component components[MAX_COMPONENTS];
    u32 components_length;
    char identifier[MAX_STRING];
}theta_game_object;

THETA_API void theta_game_object_init(theta_game_object* obj, theta_transform transform, theta_renderable* renderable, const char* identifier);

THETA_API void theta_game_object_add_component(theta_game_object* obj, theta_component component);

THETA_API BOOL theta_game_object_has_component(theta_game_object* obj, theta_component_type type);

THETA_API theta_component theta_game_object_get_component(theta_game_object* obj, theta_component_type type);

THETA_API void theta_game_object_get_model(theta_game_object* obj, mat4 model);

/*
@brief Beware, this method will also destroy the components in the game object. Do not attempt to use components supplied to the game object after this method is called.
*/
THETA_API void theta_game_object_destroy(theta_game_object* obj);