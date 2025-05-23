#pragma once

#include "renderer/skybox.h"
#include "oglshader.h"

typedef struct {
    u32 texture_id;
}theta_skybox_opengl_specifics;

THETA_API void theta_skybox_init_opengl(theta_skybox* skybox, char texture_locations[6][MAX_STRING]);

THETA_API void theta_skybox_render_opengl(theta_skybox* skybox);

THETA_API void theta_skybox_bind_vp_opengl(theta_skybox* skybox, mat4 view, mat4 projection);