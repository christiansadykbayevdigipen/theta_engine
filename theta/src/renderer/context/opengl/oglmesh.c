#include "oglmesh.h"

#include <malloc.h>
#include <memory.h>

#include "renderer/context/opengl/oglcontext.h"
#include "renderer/renderer.h"
#include "oglshader.h"
#include "ogltexture.h"

void theta_mesh_init_opengl(theta_mesh* mesh, f32* vertices, u32 number_of_vertices, u32 dimension, u32* indices, u32 number_of_indices, f32* normals, u32 number_of_normals, f32* uvs, u32 number_of_uvs, theta_mesh_face_type face_type) {
    THETA_PROFILE();
    
    theta_rendering_context* ctx = theta_renderer_get_context();

    mesh->uninterpreted_data = malloc(sizeof(theta_mesh_opengl_specifics));
    mesh->face_type = face_type;

    theta_mesh_opengl_specifics* self = DATA_CAST(theta_mesh_opengl_specifics, mesh);

    self->uses_ibo = FALSE;

    theta_rendering_context_vao_init(ctx, &self->vao);

    // Initialize the Vertex Buffer for VERTICES
    theta_opengl_vertex_buffer vbo_vertices;
    theta_rendering_context_vbo_init(ctx, &vbo_vertices, vertices, number_of_vertices*sizeof(f32));
    theta_opengl_vao_layout vertices_layout;
    vertices_layout.dimension = dimension;
    vertices_layout.index = 0;
    vertices_layout.offset = 0;
    vertices_layout.stride = sizeof(f32)*dimension;
    theta_rendering_context_vao_push_vbo(ctx, &self->vao, &vbo_vertices, &vertices_layout, 1);
    theta_rendering_context_vbo_destroy(ctx, &vbo_vertices);

    if(number_of_uvs > 0) {
        // Initialize the Vertex Buffer for UVS
        theta_opengl_vertex_buffer vbo_uvs;
        theta_rendering_context_vbo_init(ctx, &vbo_uvs, uvs, number_of_uvs * sizeof(f32));
        theta_opengl_vao_layout uvs_layout;
        uvs_layout.dimension = 2;
        uvs_layout.index = 1;
        uvs_layout.offset = 0;
        uvs_layout.stride = sizeof(f32) * 2;
        theta_rendering_context_vao_push_vbo(ctx, &self->vao, &vbo_uvs, &uvs_layout, 1);
        theta_rendering_context_vbo_destroy(ctx, &vbo_uvs);
    }

    if(number_of_normals > 0) {
        theta_opengl_vertex_buffer vbo_normals;
        theta_rendering_context_vbo_init(ctx, &vbo_normals, normals, number_of_normals*sizeof(f32));
        theta_opengl_vao_layout normals_layout;
        normals_layout.dimension = 3;
        normals_layout.index = 2;
        normals_layout.offset = 0;
        normals_layout.stride = sizeof(f32)*3;
        theta_rendering_context_vao_push_vbo(ctx, &self->vao, &vbo_normals, &normals_layout, 1);
        
        theta_rendering_context_vbo_destroy(ctx, &vbo_normals);
    }
    

    // Check to see if there are indices. If so, create an index buffer
    if(number_of_indices > 0) {
        self->uses_ibo = TRUE;

        theta_rendering_context_ibo_init(ctx, &self->ibo, indices, number_of_indices);
    }

    mesh->vertex_position_count = number_of_vertices/dimension;


    /*Setup Function Pointers Here*/
    mesh->render = &theta_mesh_render_opengl;
    mesh->destroy = &theta_mesh_destroy_opengl;
}

void theta_mesh_render_opengl(theta_mesh* mesh, theta_shader_program* program) {
    theta_rendering_context* ctx = theta_renderer_get_context();
    theta_mesh_opengl_specifics* self = DATA_CAST(theta_mesh_opengl_specifics, mesh);

    theta_rendering_context_draw(ctx, &self->vao, mesh->vertex_position_count, program, self->uses_ibo, &self->ibo, mesh->face_type);
}

void theta_mesh_destroy_opengl(theta_mesh* mesh) {
    THETA_PROFILE();

    theta_rendering_context* ctx = theta_renderer_get_context();
    theta_mesh_opengl_specifics* self = DATA_CAST(theta_mesh_opengl_specifics, mesh);
    theta_rendering_context_vao_destroy(ctx, &self->vao);
}