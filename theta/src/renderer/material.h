#pragma once

#include "core.h"
#include "shader.h"
#include "texture.h"

typedef struct theta_material{
    BOOL uses_albedo;
    theta_texture* albedo;
    f32 texture_tiling_x;
    f32 texture_tiling_y;
    BOOL uses_color;
    vec3 color;
    f32 metallic, roughness, ao; // THERE ARE ALL FOR TESTING PURPOSES REMOVE LATER.
    BOOL lighted; // Determines whether the material will have light sources affecting it.
    BOOL is_skybox;
}theta_material;

THETA_API void theta_material_bind_to_shader(theta_material* material, theta_shader_program* shader_program);