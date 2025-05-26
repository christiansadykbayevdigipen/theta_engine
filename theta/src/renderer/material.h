#pragma once

#include "core.h"
#include "shader.h"
#include "texture.h"

typedef struct theta_material{
    theta_texture* albedo;
    f32 texture_tiling_x;
    f32 texture_tiling_y;
    BOOL uses_color;
    vec3 color;
    f32 metallic, roughness, ao;
    theta_texture* metallic_map;
    theta_texture* roughness_map;
    theta_texture* ao_map;
    theta_texture* normal_map;
    BOOL lighted; // Determines whether the material will have light sources affecting it.
    BOOL is_skybox;
}theta_material;

THETA_API void theta_material_bind_to_shader(theta_material* material, theta_shader_program* shader_program);