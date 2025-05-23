#include "skybox.h"

#include "renderer.h"

#include "context/opengl/oglskybox.h"

void theta_skybox_init(theta_skybox* skybox, char texture_locations[6][MAX_STRING]) {
    THETA_PROFILE();

    switch(theta_renderer_get_api()) {
    case THETA_API_OPENGL:
        theta_skybox_init_opengl(skybox, texture_locations);
        break;
    default:
        return;
    }
}