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
THETA_API void theta_renderable_init_quad(theta_renderable* renderable, const char* textureFilepath);


THETA_API void theta_renderable_destroy(theta_renderable* renderable);