#pragma once

#include "core.h"

#include "material.h"
#include "mesh.h"

/*
@brief The full renderer attached to an object. 
*/
typedef struct theta_renderable {
    theta_mesh mesh;
    theta_material material;
}theta_renderable;

/*
@brief Initializes a quad renderable.
*/
THETA_API theta_renderable* theta_renderable_init_quad(const char* textureFilepath);

// Initializes a quad with a color supplied
THETA_API theta_renderable* theta_renderable_init_quad_colored(theta_vector3f color);

THETA_API theta_renderable* theta_renderable_init_cube_colored(theta_vector3f color);

THETA_API void theta_renderable_destroy(theta_renderable* renderable);