#pragma once

#include "core.h"

#include "renderer/texture.h"

typedef struct {
    u32 texture_id;
}theta_texture_opengl_specifics;

THETA_API theta_texture* theta_texture_init_opengl(const char* filepath);
THETA_API theta_texture* theta_texture_initw_opengl(const char* filepath, theta_texture_wrap_type wrap_type);