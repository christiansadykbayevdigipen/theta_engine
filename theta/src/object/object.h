#pragma once

#include "core.h"

#include "renderer/renderable.h"
#include <cglm/cglm.h>
#include "transform.h"

#define MAX_COMPONENTS 30

typedef enum {
    THETA_COMPONENT_TYPE_NULL,
    THETA_COMPONENT_TYPE_RENDERABLE,
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

// Creates a game object that requires a pointer to an uninitialized game object structure. 
// The identifier is essentially the "name" of the game object. No two game objects can have the same identifier.
THETA_API void theta_game_object_init(theta_game_object* obj, theta_transform transform, theta_renderable* renderable, const char* identifier);

// Adds a component to the game object's component-stack. There is a maximum of MAX_COMPONENTS allowed per game object.
THETA_API void theta_game_object_add_component(theta_game_object* obj, theta_component component);

// Checks to see if a game object has a particular component
THETA_API BOOL theta_game_object_has_component(theta_game_object* obj, theta_component_type type);

// Gets a component associated with the game object. Takes in the component type and spits out only one component (There can only be one component for each type of component in a game object). If it did not find a component of the specified component type, it will return a blank component with a type of THETA_COMPONENT_TYPE_NULL
THETA_API theta_component theta_game_object_get_component(theta_game_object* obj, theta_component_type type);

// Gets the model matrix associated with the game object
THETA_API void theta_game_object_get_model(theta_game_object* obj, mat4 model);

//  This method will destroy all associated components and will destroy itself.
THETA_API void theta_game_object_destroy(theta_game_object* obj);