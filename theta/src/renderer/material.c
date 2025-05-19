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
}