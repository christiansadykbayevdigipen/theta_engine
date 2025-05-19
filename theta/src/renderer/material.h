#pragma once

#include "core.h"
#include "shader.h"
#include "texture.h"

typedef struct {
    BOOL uses_albedo;
    theta_texture* albedo;
    BOOL uses_color;
    theta_vector3f color;
}theta_material;

THETA_API void theta_material_bind_to_shader(theta_material* material, theta_shader_program* shader_program);