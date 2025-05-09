#pragma once

#include "core.h"
#include "shader.h"
#include "texture.h"

typedef struct {
    theta_shader_program program;
    theta_texture albedo;
}theta_material;

/*
@brief This creates a theta material.
@param program A pointer to an uninitialized material structure
@param type The type of shader to initialize.
*/
THETA_API void theta_material_init(theta_material* material, theta_shader_type type, const char* textureFilepath);

THETA_API void theta_material_destroy(theta_material* material);