#pragma once

#include "core.h"
#include "renderer/mesh.h"

THETA_API void theta_mesh_init_opengl(theta_mesh* mesh, f32* vertices, u32 number_of_vertices, u32 dimension);

THETA_API void theta_mesh_render_opengl(theta_mesh* mesh);