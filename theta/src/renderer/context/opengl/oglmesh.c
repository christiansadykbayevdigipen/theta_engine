#include "oglmesh.h"

#include <malloc.h>
#include <memory.h>

#include "renderer/context/opengl/oglcontext.h"
#include "renderer/renderer.h"

typedef struct {
    theta_opengl_vertex_array vao;
}theta_mesh_opengl_specifics;

void theta_mesh_init_opengl(theta_mesh* mesh, f32* vertices, u32 number_of_vertices, u32 dimension) {
    theta_rendering_context* ctx = theta_renderer_get_context();

    theta_dynamic_list_init_args(&mesh->vertices, vertices, sizeof(f32), number_of_vertices);

    mesh->uninterpreted_data = malloc(sizeof(theta_mesh_opengl_specifics));

    theta_mesh_opengl_specifics* self = DATA_CAST(theta_mesh_opengl_specifics, mesh);

    theta_rendering_context_vao_init(ctx, &self->vao);

    theta_opengl_vertex_buffer vbo;

    theta_opengl_vao_layout layout;
    layout.dimension = dimension;
    layout.index = 0;
    layout.offset = 0;
    layout.stride = sizeof(f32) * dimension;

    theta_rendering_context_vbo_init(ctx, &vbo, vertices, sizeof(f32) * number_of_vertices);

    theta_rendering_context_vao_push_vbo(ctx, &self->vao, &vbo, layout);

    mesh->render = &theta_mesh_render_opengl;
    mesh->vertex_position_count = number_of_vertices / dimension;
}

void theta_mesh_render_opengl(theta_mesh* mesh) {
    theta_rendering_context* ctx = theta_renderer_get_context();
    theta_mesh_opengl_specifics* self = DATA_CAST(theta_mesh_opengl_specifics, mesh);
    theta_rendering_context_vao_draw(ctx, &self->vao, mesh->vertex_position_count);
}