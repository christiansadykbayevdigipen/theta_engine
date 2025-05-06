#include "oglcontext.h"

#include <memory.h>
#include <malloc.h>

#include <glad/gl.h>

#include "window/platform/shared/shared_window.h"

void theta_rendering_context_init_opengl(theta_rendering_context* ctx, theta_window* window) {
    THETA_PROFILE();
    ctx->uninterpreted_data = malloc(sizeof(theta_opengl_rendering_context_specifics));
    ctx->window = window;
    ctx->api = THETA_API_OPENGL;
    
    THETA_ASSERT(gladLoadGL(theta_shared_window_get_proc_address(window)), "theta_rendering_context_init_opengl has failed. The reason being, glad, the opengl loader, has failed to load opengl.");
    
}