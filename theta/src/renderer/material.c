#include "material.h"

#include <memory.h>
#include <malloc.h>

void theta_material_bind_to_shader(theta_material* material, theta_shader_program* shader_program) {
    THETA_PROFILE();

    shader_program->give_material(shader_program, material);
}