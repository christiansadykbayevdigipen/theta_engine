#pragma once

#include "core.h"
#include "shader.h"

// Initializes the shader library
THETA_API void theta_shader_library_init();

// Adds a shader to the shader library with a special identifier that is associated with that shader
// In essense, you can get the shader just by name.
THETA_API void theta_shader_library_add(theta_shader_program program, const char* identifier);

// Gets a shader by the name associated with it. Must already have been added to the shader library
// If not, this will return an unfilled structure.
THETA_API theta_shader_program theta_shader_library_copy(const char* identifier);

// Frees all memory associated with the shader library.
THETA_API void theta_shader_library_destroy();