#include "material.h"

#include <memory.h>
#include <malloc.h>

void theta_material_bind_to_shader(theta_material* material, theta_shader_program* shader_program) {
    THETA_PROFILE();

    if(material->uses_albedo) {
        shader_program->give_albedo(shader_program, material->albedo);
    }
    
    if(material->uses_color){
        shader_program->set_color(shader_program, material->color);
    }

    if(material->lighted) {
        // All the lighting stuff goes here

        shader_program->set_specular(shader_program, material->specular_strength);
        shader_program->set_specular_highlight(shader_program, material->specular_highlight);
    }
}