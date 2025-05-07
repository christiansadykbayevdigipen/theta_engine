#pragma once

#include "core.h"
#include "math/tmath.h"

typedef struct theta_shader_program{
    void* uninterpreted_data;
}theta_shader_program;

/*
@brief Initializes a shader program for theta.
@param program A pointer to an uninitialized theta_shader_program structure
@param filename The location of the full shader program with both Pixel and Vertex shaders mixed together.
*/
THETA_API void theta_shader_program_init(theta_shader_program* program, const char* filename);