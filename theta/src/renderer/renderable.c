#include "renderable.h"

#include <memory.h>
#include <malloc.h>

void theta_renderable_init_quad(theta_renderable* renderable) {
    f32 quad[] = {
            // first triangle
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f,  0.5f, 0.0f,  // top left 
    // second triangle
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left
    };

    theta_mesh_init(&renderable->mesh, quad, sizeof(quad) / sizeof(f32), 3);
    theta_material_init(&renderable->material, THETA_SHADER_TYPE_BASIC_SHADER);
}

void theta_renderable_destroy(theta_renderable* renderable) {
    renderable->mesh.destroy(&renderable->mesh);
    theta_material_destroy(&renderable->material);
}