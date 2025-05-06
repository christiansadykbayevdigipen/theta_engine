#pragma once

#include "core.h"
#include "renderer/context/context.h"

typedef struct {
    u32 proc_address;
}theta_opengl_rendering_context_specifics;

THETA_API void theta_rendering_context_init_opengl(theta_rendering_context* ctx, theta_window* window);