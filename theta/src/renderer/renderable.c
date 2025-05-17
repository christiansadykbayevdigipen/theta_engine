#include "renderable.h"

#include <memory.h>
#include <malloc.h>

static f32 g_quad_vertices[] = {
    // positions
    0.5f,
    0.5f,
    0.0f,
    0.5f,
    -0.5f,
    0.0f,
    -0.5f,
    -0.5f,
    0.0f,
    -0.5f,
    0.5f,
    0.0f,
};

static f32 g_quad_texture_coordinates[] = {
    // texture coords
    1.0f, 1.0f, // top right
    1.0f, 0.0f, // bottom right
    0.0f, 0.0f, // bottom left
    0.0f, 1.0f  // top left
};

static u32 g_quad_indices[] = {
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
};



static f32 g_cube_vertices[] = {
        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f, 
        0.5f,  0.5f, -0.5f, 
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        0.5f, -0.5f,  0.5f, 
        0.5f,  0.5f,  0.5f, 
        -0.5f,  0.5f,  0.5f,
 
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        0.5f, -0.5f, -0.5f, 
        0.5f,  0.5f, -0.5f, 
        0.5f,  0.5f,  0.5f, 
        0.5f, -0.5f,  0.5f, 
 
        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f, 
        0.5f, -0.5f,  0.5f, 
        -0.5f, -0.5f,  0.5f,
        0.5f,  0.5f, -0.5f, 
        -0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f,  0.5f,
        0.5f,  0.5f,  0.5f, 
};

static f32 g_cube_tex_coords[] = {
  0.0f, 0.0f,  // A 0
 1.0f, 0.0f,  // B 1
 1.0f, 1.0f,  // C 2
  0.0f, 1.0f,  // D 3
  0.0f, 0.0f,  // E 4
 1.0f, 0.0f,   // F 5
 1.0f, 1.0f,   // G 6
  0.0f, 1.0f,   // H 7
  0.0f, 0.0f,  // D 8
  1.0f, 0.0f,  // A 9
  1.0f, 1.0f,  // E 10
  0.0f, 1.0f,  // H 11
 0.0f, 0.0f,   // B 12
 1.0f, 0.0f,   // C 13
 1.0f, 1.0f,   // G 14
 0.0f, 1.0f,   // F 15
  0.0f, 0.0f,  // A 16
 1.0f, 0.0f,   // B 17
 1.0f, 1.0f,   // F 18
  0.0f, 1.0f,  // E 19
  0.0f, 0.0f,  // C 20
  1.0f, 0.0f,  // D 21
  1.0f, 1.0f,  // H 22
  0.0f, 1.0f,  // G 23
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


theta_renderable* theta_renderable_init_quad(const char* textureFilepath) {
    THETA_PROFILE();

    theta_renderable* renderable = INIT_STRUCT(theta_renderable);

    theta_mesh_init(&renderable->mesh, g_quad_vertices, sizeof(g_quad_vertices) / sizeof(f32), 3, g_quad_indices, sizeof(g_quad_indices) / sizeof(u32), g_quad_texture_coordinates, sizeof(g_quad_texture_coordinates) / sizeof(f32));
    theta_material_init(&renderable->material, THETA_SHADER_TYPE_BASIC_SHADER_TEXTURED, textureFilepath);

    return renderable;
}

theta_renderable* theta_renderable_init_quad_colored(theta_vector3f color) {
    THETA_PROFILE();

    theta_renderable* renderable = INIT_STRUCT(theta_renderable);

    theta_mesh_init(&renderable->mesh, g_quad_vertices, sizeof(g_quad_vertices) / sizeof(f32), 3, g_quad_indices, sizeof(g_quad_indices) / sizeof(u32), g_quad_texture_coordinates, sizeof(g_quad_texture_coordinates) / sizeof(f32));
    theta_material_init_colored(&renderable->material, THETA_SHADER_TYPE_BASIC_SHADER_COLORED, color);

    return renderable;
}

theta_renderable* theta_renderable_init_cube(const char* textureFilepath, theta_texture_wrap_type wrap_type) {
    THETA_PROFILE();

    theta_renderable* renderable = INIT_STRUCT(theta_renderable);

    theta_mesh_init(&renderable->mesh, g_cube_vertices, sizeof(g_cube_vertices) / sizeof(f32), 3, g_cube_indices, sizeof(g_cube_indices) / sizeof(u32), g_cube_tex_coords, sizeof(g_cube_tex_coords) / sizeof(f32));
    theta_material_init(&renderable->material, THETA_SHADER_TYPE_BASIC_SHADER_TEXTURED, textureFilepath);

    return renderable;
}

theta_renderable* theta_renderable_init_cube_colored(theta_vector3f color) {
    THETA_PROFILE();

    theta_renderable* renderable = INIT_STRUCT(theta_renderable);

    theta_mesh_init(&renderable->mesh, g_cube_vertices, sizeof(g_cube_vertices) / sizeof(f32), 3, g_cube_indices, sizeof(g_cube_indices) / sizeof(u32), g_cube_tex_coords, sizeof(g_cube_tex_coords) / sizeof(f32));
    theta_material_init_colored(&renderable->material, THETA_SHADER_TYPE_BASIC_SHADER_COLORED, color);

    return renderable;
}

theta_renderable* theta_renderable_init(const char* mesh_location, const char* texture_filepath, theta_texture_wrap_type wrap_type) {
    /*Initialize all of the lists.*/
    
    theta_dynamic_list vertex_indices;
    theta_dynamic_list_init(&vertex_indices, sizeof(u32));
    theta_dynamic_list uv_indices;
    theta_dynamic_list_init(&uv_indices, sizeof(u32));
    theta_dynamic_list normal_indices;
    theta_dynamic_list_init(&normal_indices, sizeof(u32));

    theta_dynamic_list temp_vertices;
    theta_dynamic_list_init(&temp_vertices, sizeof(f32));
    theta_dynamic_list temp_uvs;
    theta_dynamic_list_init(&temp_uvs, sizeof(f32));
    theta_dynamic_list temp_normals;
    theta_dynamic_list_init(&temp_normals, sizeof(f32));


    
}

void theta_renderable_destroy(theta_renderable* renderable) {
    THETA_PROFILE();

    renderable->mesh.destroy(&renderable->mesh);
    theta_material_destroy(&renderable->material);
}