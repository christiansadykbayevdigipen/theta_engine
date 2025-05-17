#include "material.h"

#include <memory.h>
#include <malloc.h>

void theta_material_init(theta_material* material, theta_shader_type type, const char* textureFilepath) {
    THETA_PROFILE();
    theta_shader_program_init_type(&material->program, type);

    material->program.give_albedo(&material->program, theta_texture_init(textureFilepath));

    material->albedo_in_use = TRUE;
}

void theta_material_destroy(theta_material* material) {
    THETA_PROFILE();

    material->program.destroy(&material->program);
}

void theta_material_init_colored(theta_material* material, theta_shader_type type, theta_vector3f color) {
    THETA_PROFILE();

    theta_shader_program_init_type(&material->program, type);

    material->albedo_in_use = FALSE;

    material->program.set_color(&material->program, color);
}