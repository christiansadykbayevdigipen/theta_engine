#pragma once

#include "renderer/uniform_buffer.h"

typedef struct {
    u32 id;
}theta_uniform_buffer_opengl_specifics;

THETA_API void theta_uniform_buffer_init_opengl(theta_uniform_buffer* buffer, u64 data_size, const char* associated_name);

THETA_API void theta_uniform_buffer_update_data_opengl(theta_uniform_buffer* buffer, void* data);