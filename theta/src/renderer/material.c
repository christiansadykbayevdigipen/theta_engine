#include "material.h"

#include <memory.h>
#include <malloc.h>

void theta_material_init(theta_material* material, theta_shader_type type, const char* textureFilepath) {
    THETA_PROFILE();
    theta_shader_program_init_type(&material->program, type);

    material->program.give_albedo(&material->program, textureFilepath);
}

void theta_material_destroy(theta_material* material) {
    THETA_PROFILE();

    material->program.destroy(&material->program);
}