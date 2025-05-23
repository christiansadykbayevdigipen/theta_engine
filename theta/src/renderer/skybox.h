#pragma once

#include "core.h"
#include "mesh.h"
#include "shader.h"
#include "material.h"

typedef struct theta_skybox{
    theta_mesh cubemap_mesh;
    theta_shader_program program;
    void* uninterpreted_data;
    void (*render)(struct theta_skybox* skybox);
    void (*bind_vp)(struct theta_skybox* skybox, mat4 view, mat4 proj);
}theta_skybox;

// Initializes a skybox.
// The texture locations should include an array of 6 texture locations: the right component, left, top, bottom, front, and back components. All in that order.
// 0->Right
// 1->Left
// 2->Top
// 3->Bottom
// 4->Front
// 5->Back
THETA_API void theta_skybox_init(theta_skybox* skybox, char texture_locations[6][MAX_STRING]);