#include "context.h"

#include "opengl/oglcontext.h"

void theta_rendering_context_init(theta_rendering_context* ctx, theta_api api, theta_window* window) {
    THETA_PROFILE();
    switch(api) {
    case THETA_API_OPENGL:
        theta_rendering_context_init_opengl(ctx, window);
        break;
    default:
        THETA_FATAL("theta_rendering_context_init has failed. The reason being, the API requested either does not exist or is not implemented yet.\n");
        break;
    }
}