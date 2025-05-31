#pragma once

#include "core.h"

// Allows you to pass a structure into a shader.
typedef struct theta_uniform_buffer{
    void* uninterpreted_data;
    u64 data_size;
    char name[MAX_STRING];

    void (*update_data)(struct theta_uniform_buffer* buffer, void* data);
}theta_uniform_buffer;

// Creates a uniform buffer with the data size specified in bytes.
// This is useful if you want to pass in a structure directly into your shader program.
// The associated_name must be the same as the one supplied in the shader program.
THETA_API void theta_uniform_buffer_init(theta_uniform_buffer* buffer, u64 data_size, const char* associated_name);