#include "oglmesh.h"

#include <malloc.h>
#include <memory.h>

#include "renderer/context/opengl/oglcontext.h"
#include "renderer/renderer.h"
#include "oglshader.h"
#include "ogltexture.h"

typedef struct {
    theta_opengl_vertex_array vao;
    theta_opengl_index_buffer ibo;
}theta_mesh_opengl_specifics;

void theta_mesh_init_opengl(theta_mesh* mesh, f32* vertices, u32 number_of_vertices, u32 dimension, u32* indices, u32 number_of_indices, f32* normals, u32 number_of_normals) {
    THETA_PROFILE();
    
    theta_rendering_context* ctx = theta_renderer_get_context();

    mesh->uninterpreted_data = malloc(sizeof(theta_mesh_opengl_specifics));

    theta_mesh_opengl_specifics* self = DATA_CAST(theta_mesh_opengl_specifics, mesh);

    theta_rendering_context_vao_init(ctx, &self->vao);

    theta_opengl_vertex_buffer vbo;
    theta_opengl_vertex_buffer normals_vbo;

    theta_opengl_vao_layout layout;
    layout.dimension = dimension;
    layout.index = 0;
    layout.offset = 0;
    layout.stride = sizeof(f32) * (dimension+2);

    theta_opengl_vao_layout tex_layout;
    tex_layout.dimension = 2;
    tex_layout.index = 1;
    tex_layout.offset = sizeof(f32) * 3;
    tex_layout.stride = sizeof(f32) * 5;

    theta_opengl_vao_layout layouts[2] = {layout, tex_layout};

    theta_rendering_context_vbo_init(ctx, &vbo, vertices, sizeof(f32) * number_of_vertices);

    
    
    theta_rendering_context_vao_push_vbo(ctx, &self->vao, &vbo, layouts, 2);
    
    if(number_of_normals > 0) {
        theta_rendering_context_vbo_init(ctx, &normals_vbo, normals, sizeof(f32) * number_of_normals);
        theta_opengl_vao_layout normals_layout;
        normals_layout.dimension = 3;
        normals_layout.index = 2;
        normals_layout.offset = 0;
        normals_layout.stride = sizeof(f32) * 3;
        theta_rendering_context_vao_push_vbo(ctx, &self->vao, &normals_vbo, &normals_layout, 1);
    }

    mesh->vertex_position_count = number_of_vertices / dimension;

    theta_rendering_context_ibo_init(ctx, &self->ibo, indices, number_of_indices);
    
    /*Setup Function Pointers Here*/
    mesh->render = &theta_mesh_render_opengl;
    mesh->destroy = &theta_mesh_destroy_opengl;
}

void theta_mesh_render_opengl(theta_mesh* mesh, theta_shader_program* program) {
    theta_rendering_context* ctx = theta_renderer_get_context();
    theta_mesh_opengl_specifics* self = DATA_CAST(theta_mesh_opengl_specifics, mesh);

    theta_rendering_context_vao_draw(ctx, &self->vao, mesh->vertex_position_count, program, &self->ibo);
}

void theta_mesh_destroy_opengl(theta_mesh* mesh) {
    THETA_PROFILE();

    theta_rendering_context* ctx = theta_renderer_get_context();
    theta_mesh_opengl_specifics* self = DATA_CAST(theta_mesh_opengl_specifics, mesh);
    theta_rendering_context_vao_destroy(ctx, &self->vao);
}