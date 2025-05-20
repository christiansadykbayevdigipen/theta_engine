#pragma once

#include "core.h"

#include "material.h"
#include "mesh.h"
#include "texture.h"

/*
@brief The full renderer attached to an object. 
*/
typedef struct theta_renderable {
    theta_mesh mesh;
    theta_shader_program program;
    theta_material material;
}theta_renderable;

// /*
// @brief Initializes a quad renderable.
// */
// THETA_API theta_renderable* theta_renderable_init_quad(const char* texture_filepath);

// // Initializes a quad with a color supplied
// THETA_API theta_renderable* theta_renderable_init_quad_colored(theta_vector3f color);

// THETA_API theta_renderable* theta_renderable_init_cube(const char* texture_filepath, theta_texture_wrap_type wrap_type);

// THETA_API theta_renderable* theta_renderable_init_cube_colored(theta_vector3f color);

// // Currently unimplemented.
// THETA_API theta_renderable* theta_renderable_init(const char* mesh_location, const char* texture_filepath, theta_texture_wrap_type wrap_type);

THETA_API theta_renderable* theta_renderable_init(theta_mesh mesh, theta_material material, theta_shader_program shader_program);

THETA_API void theta_renderable_destroy(theta_renderable* renderable);