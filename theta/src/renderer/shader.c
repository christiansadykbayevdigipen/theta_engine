#include "shader.h"

#include "renderer/renderer.h"

#include "context/opengl/oglshader.h"

void theta_shader_program_init(theta_shader_program* program, const char* filename) {
    THETA_PROFILE();

    switch(theta_renderer_get_api()) {
    case THETA_API_OPENGL:
        theta_shader_program_init_opengl(program, filename);
        break;
    default:
        return;
    }
}

void theta_shader_program_init_type(theta_shader_program* program, theta_shader_type type) {
    THETA_PROFILE();

    switch(type) {
    case THETA_SHADER_TYPE_BASIC_SHADER_TEXTURED:
        theta_shader_program_init(program, "res/basic_shader_textured.shader");
        break;
    case THETA_SHADER_TYPE_BASIC_SHADER_COLORED:
        theta_shader_program_init(program, "res/basic_shader_colored.shader");
        break;
    default:
        THETA_ERROR("theta_shader_program_init_type has failed. The reason being, the shader type given to theta_shader_program_init_type either does not exist, or has not been implemented yet!\n");
        return;
        break;
    }
    
}