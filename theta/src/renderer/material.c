#include "material.h"

#include <memory.h>
#include <malloc.h>

void theta_material_init(theta_material* material, theta_shader_type type) {
    theta_shader_program_init_type(&material->program, type);
}

void theta_material_destroy(theta_material* material) {
    material->program.destroy(&material->program);
}