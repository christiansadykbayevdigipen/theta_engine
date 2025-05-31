#include "uniform_buffer.h"

#include "renderer.h"
#include "renderer/context/opengl/ogluniform_buffer.h"

void theta_uniform_buffer_init(theta_uniform_buffer* buffer, u64 data_size, const char* associated_name) {
    switch(theta_renderer_get_api()) {
    case THETA_API_OPENGL:
        theta_uniform_buffer_init_opengl(buffer, data_size, associated_name);
        break;
    default:
        return;
    }
}