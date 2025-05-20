#include "mesh.h"

#include "renderer/renderer.h"

#include "context/opengl/oglcontext.h"
#include "context/opengl/oglmesh.h"

#include "fast_obj.h"

static f32 g_quad_vertices[] = {
    // positions           coords
     0.5f,  0.5f, 0.0f,       // top right
     0.5f, -0.5f, 0.0f,       // bottom right
    -0.5f, -0.5f, 0.0f,       // bottom left
    -0.5f,  0.5f, 0.0f,       // top left 
};

static f32 g_quad_tex_coords[] = {
    // texture 
1.0f, 1.0f,
1.0f, 0.0f,
0.0f, 0.0f,
0.0f, 1.0f 
};

static u32 g_quad_indices[] = {
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
};



static f32 g_cube_vertices[] = {
        -0.5f, -0.5f, -0.5f,  // A 0
        0.5f, -0.5f, -0.5f,  // B 1
        0.5f,  0.5f, -0.5f,  // C 2
        -0.5f,  0.5f, -0.5f,  // D 3
        -0.5f, -0.5f,  0.5f,  // E 4
        0.5f, -0.5f,  0.5f,   // F 5
        0.5f,  0.5f,  0.5f,   // G 6
        -0.5f,  0.5f,  0.5f,   // H 7
        -0.5f,  0.5f, -0.5f,  // D 8
        -0.5f, -0.5f, -0.5f,  // A 9
        -0.5f, -0.5f,  0.5f,  // E 10
        -0.5f,  0.5f,  0.5f,  // H 11
        0.5f, -0.5f, -0.5f,   // B 12
        0.5f,  0.5f, -0.5f,   // C 13
        0.5f,  0.5f,  0.5f,   // G 14
        0.5f, -0.5f,  0.5f,   // F 15
        -0.5f, -0.5f, -0.5f,  // A 16
        0.5f, -0.5f, -0.5f,   // B 17
        0.5f, -0.5f,  0.5f,   // F 18
        -0.5f, -0.5f,  0.5f,  // E 19
        0.5f,  0.5f, -0.5f,   // C 20
        -0.5f,  0.5f, -0.5f,  // D 21
        -0.5f,  0.5f,  0.5f,  // H 22
        0.5f,  0.5f,  0.5f,   // G 23
};

static f32 g_cube_tex_coords[] = {
      0.0f, 0.0f,
 1.0f, 0.0f, 
 1.0f, 1.0f, 
  0.0f, 1.0f,
  0.0f, 0.0f,
 1.0f, 0.0f, 
 1.0f, 1.0f, 
  0.0f, 1.0f,
  0.0f, 0.0f,
  1.0f, 0.0f,
  1.0f, 1.0f,
  0.0f, 1.0f,
 0.0f, 0.0f, 
 1.0f, 0.0f, 
 1.0f, 1.0f, 
 0.0f, 1.0f, 
  0.0f, 0.0f,
 1.0f, 0.0f, 
 1.0f, 1.0f, 
  0.0f, 1.0f,
  0.0f, 0.0f,
  1.0f, 0.0f,
  1.0f, 1.0f,
  0.0f, 1.0f,
};

static f32 g_cube_normals[] =
{
   0.0f, 0.0f, -1.0f,
   0.0f, 0.0f, -1.0f,
   0.0f, 0.0f, -1.0f,
   0.0f, 0.0f, -1.0f,
   0.0f, 0.0f, 1.0f, 
   0.0f, 0.0f, 1.0f, 
   0.0f, 0.0f, 1.0f, 
   0.0f, 0.0f, 1.0f, 
  -1.0f, 0.0f, 0.0f, 
  -1.0f, 0.0f, 0.0f, 
  -1.0f, 0.0f, 0.0f, 
  -1.0f, 0.0f, 0.0f, 
   1.0f, 0.0f, 0.0f, 
   1.0f, 0.0f, 0.0f, 
   1.0f, 0.0f, 0.0f, 
   1.0f, 0.0f, 0.0f, 
   0.0f, -1.0f, 0.0f,
   0.0f, -1.0f, 0.0f,
   0.0f, -1.0f, 0.0f,
   0.0f, -1.0f, 0.0f,
   0.0f, 1.0f, 0.0f, 
   0.0f, 1.0f, 0.0f, 
   0.0f, 1.0f, 0.0f, 
   0.0f, 1.0f, 0.0f  
};

static u32 g_cube_indices[] = {
        // front and back
        0, 3, 2,
        2, 1, 0,
        4, 5, 6,
        6, 7 ,4,
        // left and right
        11, 8, 9,
        9, 10, 11,
        12, 13, 14,
        14, 15, 12,
        // bottom and top
        16, 17, 18,
        18, 19, 16,
        20, 21, 22,
        22, 23, 20
};

void theta_mesh_init(theta_mesh* mesh, f32* vertices, u32 number_of_vertices, u32 dimension, u32* indices, u32 number_of_indices, f32* normals, u32 number_of_normals, f32* uvs, u32 number_of_uvs) {
    THETA_PROFILE();

    switch(theta_renderer_get_api()) {
    case THETA_API_OPENGL:
        theta_mesh_init_opengl(mesh, vertices, number_of_vertices, dimension, indices, number_of_indices, normals, number_of_normals, uvs, number_of_uvs);
        break;
    default:
        THETA_FATAL("theta_mesh_init has failed. The reason being, an unsupported or non existent API was supplied to theta_mesh_init.\n");
        break;
    }
}

void theta_mesh_init_quad(theta_mesh* mesh) {
    theta_mesh_init(mesh, g_quad_vertices, sizeof(g_quad_vertices) / sizeof(g_quad_vertices[0]), 3, g_quad_indices, sizeof(g_quad_indices) / sizeof(g_quad_indices[0]), NULL, 0, g_quad_tex_coords, sizeof(g_quad_tex_coords) / sizeof(g_quad_tex_coords[0]));
}

void theta_mesh_init_cube(theta_mesh* mesh) {
    theta_mesh_init(mesh, g_cube_vertices, sizeof(g_cube_vertices) / sizeof(g_cube_vertices[0]), 3, g_cube_indices, sizeof(g_cube_indices)/sizeof(g_cube_indices[0]), g_cube_normals, sizeof(g_cube_normals)/sizeof(g_cube_normals[0]), g_cube_tex_coords, sizeof(g_cube_tex_coords) / sizeof(g_cube_tex_coords[0]));
}

void theta_mesh_init_from_file(theta_mesh* mesh, const char* filename) {
    fastObjMesh* m = fast_obj_read(filename);

    THETA_ASSERT(m, "theta_mesh_init_from_file has failed. The reason being, the filename does not exist!");

    for(s32 i = 0; i < m->index_count; i++) {
        
        u32 test = m->position_count;
        m->indices[i].p;
    }
}