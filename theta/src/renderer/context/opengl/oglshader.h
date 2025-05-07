#pragma once 

#include "renderer/shader.h"

typedef struct {
    u32 programID;
}theta_shader_program_opengl_specifics;

THETA_API void theta_shader_program_init_opengl(theta_shader_program* program, const char* filename);