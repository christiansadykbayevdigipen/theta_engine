#pragma once

#include "core.h"
#include "utils/list.h"

/*
@brief The mesh in theta is the rendered object without any material applied. It's the shape of the rendered object.
*/
typedef struct theta_mesh {
    theta_dynamic_list vertices;
    u32 vertex_position_count;
    void* uninterpreted_data;

    void (*render)(struct theta_mesh*);
}theta_mesh;

/*
@brief Initializes a mesh with vertices
@param mesh A pointer to an uninitialized theta_mesh structure.
@param vertices The vertices to give the mesh. The positions. Assumes groups of triangles.
@param number_of_vertices The number of vertices in the list. Does not mean the number of vertex positions, rather, the number of floats in the list.
@param dimension The size of each vertex position. Is it two dimensional or three dimensional?
*/
THETA_API void theta_mesh_init(theta_mesh* mesh, f32* vertices, u32 number_of_vertices, u32 dimension);