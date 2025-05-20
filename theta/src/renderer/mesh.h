#pragma once

#include "core.h"
#include "utils/list.h"

struct theta_shader_program;

/*
@brief The mesh in theta is the rendered object without any material applied. It's the shape of the rendered object.
*/
typedef struct theta_mesh {
    u32 vertex_position_count;
    void* uninterpreted_data;

    void (*render)(struct theta_mesh*, struct theta_shader_program*);
    void (*destroy)(struct theta_mesh*);
}theta_mesh;

/*
@brief Initializes a mesh with vertices
@param mesh A pointer to an uninitialized theta_mesh structure.
@param vertices The vertices to give the mesh. The positions. Assumes groups of triangles.
@param number_of_vertices The number of vertices in the list. Does not mean the number of vertex positions, rather, the number of floats in the list.
@param dimension The size of each vertex position. Is it two dimensional or three dimensional?
@param indices The list of indices that refer to the vertices
@param number_of_indices The number of indices in the array
*/
THETA_API void theta_mesh_init(theta_mesh* mesh, f32* vertices, u32 number_of_vertices, u32 dimension, u32* indices, u32 number_of_indices, f32* normals, u32 number_of_normals, f32* uvs, u32 number_of_uvs);

// Creates a basic quad mesh with basic vertices, and UV coordinates
THETA_API void theta_mesh_init_quad(theta_mesh* mesh);

// Creates a basic cube mesh with basic vertices, UV coordinates, and normal coordinates
THETA_API void theta_mesh_init_cube(theta_mesh* mesh);

// Loads a wavefront object file into a theta mesh
THETA_API void theta_mesh_init_from_file(theta_mesh* mesh, const char* filename);