#include "context.h"

#include "opengl/oglcontext.h"

theta_rendering_context* theta_rendering_context_init(theta_api api, theta_window* window) {
    THETA_PROFILE();
    switch(api) {
    case THETA_API_OPENGL:
        return theta_rendering_context_init_opengl(window);
        break;
    default:
        THETA_FATAL("theta_rendering_context_init has failed. The reason being, the API requested either does not exist or is not implemented yet.\n");
        return NULL;
        break;
    }
}