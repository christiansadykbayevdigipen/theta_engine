#pragma once

#include "core.h"
#include "renderer/mesh.h"
#include "oglcontext.h"

struct theta_shader_program;

typedef struct {
    theta_opengl_vertex_array vao;
    theta_opengl_index_buffer ibo;
    BOOL uses_ibo;
}theta_mesh_opengl_specifics;

THETA_API void theta_mesh_init_opengl(theta_mesh* mesh, f32* vertices, u32 number_of_vertices, u32 dimension, u32* indices, u32 number_of_indices, f32* normals, u32 number_of_normals, f32* uvs, u32 number_of_uvs, theta_mesh_face_type face_type);

THETA_API void theta_mesh_render_opengl(theta_mesh* mesh, struct theta_shader_program* program);

THETA_API void theta_mesh_destroy_opengl(theta_mesh* mesh);