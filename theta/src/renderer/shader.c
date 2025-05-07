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