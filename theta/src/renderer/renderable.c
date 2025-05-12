#include "renderable.h"

#include <memory.h>
#include <malloc.h>

theta_renderable* theta_renderable_init_quad(const char* textureFilepath) {
    THETA_PROFILE();

    theta_renderable* renderable = INIT_STRUCT(theta_renderable);

    f32 quad[] = {
        // positions
        0.5f, 0.5f, 0.0f, 
        0.5f, -0.5f, 0.0f, 
        -0.5f, -0.5f, 0.0f, 
        -0.5f, 0.5f, 0.0f,
    };

    f32 quad_tex[] = {
        // texture coords
        1.0f, 1.0f, // top right
        1.0f, 0.0f, // bottom right
        0.0f, 0.0f, // bottom left
        0.0f, 1.0f  // top left
    };

    u32 indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    theta_mesh_init(&renderable->mesh, quad, sizeof(quad) / sizeof(f32), 3, indices, sizeof(indices) / sizeof(u32), quad_tex, sizeof(quad_tex) / sizeof(f32));
    theta_material_init(&renderable->material, THETA_SHADER_TYPE_BASIC_SHADER_TEXTURED, textureFilepath);

    return renderable;
}

void theta_renderable_destroy(theta_renderable* renderable) {
    THETA_PROFILE();

    renderable->mesh.destroy(&renderable->mesh);
    theta_material_destroy(&renderable->material);
}