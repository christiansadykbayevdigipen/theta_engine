#pragma once

#include "core.h"

#include "renderer/renderable.h"
#include "math/tmath.h"

#define MAX_COMPONENTS 30

// TODO: Move rotation to a quaternion system.
typedef struct {
    theta_vector3f position;
    theta_vector3f rotation;
    theta_vector3f scale;
}theta_transform;

typedef enum {
    THETA_COMPONENT_TYPE_TRANSFORM,
    THETA_COMPONENT_TYPE_CAMERA_ATTRIBS,
    THETA_COMPONENT_TYPE_RENDERABLE
}theta_component_type;

typedef struct {
    void* data;
    theta_component_type type;
}theta_component;

typedef struct {
    theta_component components[MAX_COMPONENTS];
    u32 components_length;
}theta_game_object;

THETA_API void theta_game_object_init(theta_game_object* obj);