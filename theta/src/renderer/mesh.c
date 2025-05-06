#include "mesh.h"

#include "renderer/renderer.h"

#include "context/opengl/oglcontext.h"
#include "context/opengl/oglmesh.h"

void theta_mesh_init(theta_mesh* mesh, f32* vertices, u32 number_of_vertices, u32 dimension) {
    THETA_PROFILE();

    switch(theta_renderer_get_api()) {
    case THETA_API_OPENGL:
        theta_mesh_init_opengl(mesh, vertices, number_of_vertices, dimension);
        break;
    default:
        THETA_FATAL("theta_mesh_init has failed. The reason being, an unsupported or non existent API was supplied to theta_mesh_init.\n");
        break;
    }
}