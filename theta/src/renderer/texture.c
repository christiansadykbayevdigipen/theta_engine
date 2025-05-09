#include "texture.h"

#include "renderer.h"

#include "context/opengl/ogltexture.h"

void theta_texture_init(theta_texture* texture, const char* filepath) {
    THETA_PROFILE();
    switch(theta_renderer_get_api()) {
    case THETA_API_OPENGL:
        theta_texture_init_opengl(texture, filepath);
        break;
    default:
        return;
        break;
    }
}