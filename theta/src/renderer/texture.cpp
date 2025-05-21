#include "texture.h"

#include "renderer.h"

#include "context/opengl/ogltexture.h"

theta_texture* theta_texture_init(const char* filepath) {
    THETA_PROFILE();
    switch(theta_renderer_get_api()) {
    case THETA_API_OPENGL:
        return theta_texture_init_opengl(filepath);
        break;
    default:
        return NULL;
        break;
    }
}

theta_texture* theta_texture_initw(const char* filepath, theta_texture_wrap_type wrap_type){
    THETA_PROFILE();
    switch(theta_renderer_get_api()) {
    case THETA_API_OPENGL:
        return theta_texture_initw_opengl(filepath, wrap_type);
        break;
    default:
        return NULL;
        break;
    }
}