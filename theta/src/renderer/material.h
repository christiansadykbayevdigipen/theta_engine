#pragma once

#include "core.h"
#include "shader.h"
#include "texture.h"

typedef struct theta_material{
    BOOL uses_albedo;
    theta_texture* albedo;
    BOOL uses_color;
    vec3 color;
    BOOL lighted; // Determines whether the material will have light sources affecting it.
    f32 specular_strength; // The shininess of the material. Won't really matter if the material is not lighted.
    f32 specular_highlight; // Specifies the sharpness of the highlight on the surface. This describes an exponent. The actual interpreted value in the shader will be 2^specular_highlight. A good number for this would be 5. Because 2^5=32.
    BOOL is_skybox;
}theta_material;

THETA_API void theta_material_bind_to_shader(theta_material* material, theta_shader_program* shader_program);