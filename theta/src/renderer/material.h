#pragma once

#include "core.h"
#include "shader.h"
#include "texture.h"

typedef struct {
    theta_shader_program program;
    BOOL albedo_in_use;
    theta_texture* albedo;
    theta_vector3f color;
}theta_material;

/*
@brief This creates a theta material.
@param material A pointer to an uninitialized material structure
@param type The type of shader to initialize.
*/
THETA_API void theta_material_init(theta_material* material, theta_shader_type type, const char* textureFilepath);

// This initializes a material as having a color instead of a texture.
// The albedo field in the material will be null then. Only the color will be modified. 
// The shader type must be a COLORED shader type. Not textured.
THETA_API void theta_material_init_colored(theta_material* material, theta_shader_type type, theta_vector3f color);

THETA_API void theta_material_destroy(theta_material* material);