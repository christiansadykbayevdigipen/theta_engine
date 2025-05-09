#pragma once

#include "core.h"

#include "renderer/texture.h"

typedef struct {
    u32 texture_id;
}theta_texture_opengl_specifics;

THETA_API void theta_texture_init_opengl(theta_texture* texture, const char* filepath);