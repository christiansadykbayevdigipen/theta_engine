#include "renderable.h"

#include <memory.h>
#include <malloc.h>

#define FAST_OBJ_IMPLEMENTATION
#include <fast_obj.h>



static const char* g_obj_dir = "res/";

// static void _load_obj_very_basic(const char* filename, f32** out_vertices, u32* out_vertices_len, f32** out_normals, u32* out_normals_len) {
//     theta_node* vertex_indices;
//     theta_node* uv_indices;
//     theta_node* normal_indices;
    
//     theta_node* temp_vertices;
//     theta_node* temp_uvs;
//     theta_node* temp_normals;

//     FILE* file = fopen(filename, "r");
//     if(file == NULL) {
//         printf("failed read file\n");
//         return;
//     }

//     while(TRUE) {
//         char line_header[128];

//         int res = fscanf(file, "%s", line_header);
        
//         if(res == EOF)
//             break;

        
//         if(strcmp(line_header, "v") == 0) {
//             theta_vector3f vertex;
//             fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
            
//             if(temp_vertices == NULL){
//                 temp_vertices = theta_node_init(&vertex, sizeof(vertex));
//             }else{
//                 temp_vertices = theta_node_push_back(temp_vertices, &vertex, sizeof(vertex));
//             }
//         }
//         else if(strcmp(line_header, "vn") == 0) {
//             theta_vector3f normal;
//             fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
//             if(temp_normals == NULL){
//                 temp_normals = theta_node_init(&normal, sizeof(normal));
//             }else{
//                 temp_normals = theta_node_push_back(temp_normals, &normal, sizeof(normal));
//             }
//         }
//         else if(strcmp(line_header, "f") == 0) {
//             char vertex1[50] = "", vertex2[50] = "", vertex3[50] = "";
//             u32 vertex_index[3], uv_index[3], normal_index[3];

//             s32 matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertex_index[0], &uv_index[0], &normal_index[0],
//             &vertex_index[1], &uv_index[1], &normal_index[1],
//             &vertex_index[2], &uv_index[2], &normal_index[2]);
//             if(matches != 9) {
//                 printf("cant be parsed obj too complex\n");
//                 return;
//             }

//             if(vertex_indices == NULL) {
//                 vertex_indices = theta_node_init(vertex_index, sizeof(u32));
//             }else {
//                 vertex_indices = theta_node_push_back(vertex_indices, vertex_index, sizeof(u32));
//             }
//             vertex_indices = theta_node_push_back(vertex_indices, vertex_index+1, sizeof(u32));
//             vertex_indices = theta_node_push_back(vertex_indices, vertex_index+2, sizeof(u32));
            
//             if(uv_indices == NULL) {
//                 uv_indices = theta_node_init(uv_index, sizeof(u32));
//             }else {
//                 uv_indices = theta_node_push_back(uv_indices, uv_index, sizeof(u32));
//             }
//             uv_indices = theta_node_push_back(uv_indices, uv_index+1, sizeof(u32));
//             uv_indices = theta_node_push_back(uv_indices, uv_index+2, sizeof(u32));

//             if(normal_indices == NULL) {
//                 normal_indices = theta_node_init(normal_index, sizeof(u32));
//             }else {
//                 normal_indices = theta_node_push_back(normal_indices, normal_index, sizeof(u32));
//             }
//             normal_indices = theta_node_push_back(normal_indices, normal_index+1, sizeof(u32));
//             normal_indices = theta_node_push_back(normal_indices, normal_index+2, sizeof(u32));
//         }
//     }

//     theta_node* temp = vertex_indices;
//     u32 vertices_count = 1;
//     while(temp != NULL) {
        
//         u32 vertex_index = *(u32*)temp->data;

//         theta_node* other_node = temp_vertices;
//         u32 a = 0;
//         while(other_node != NULL) {
//             if(a == vertex_index-1) {
//                 theta_vector3f vertex = *(theta_vector3f*)other_node->data;
                
//                 break;
//             }

//             other_node = other_node->next;
//             a++;
//         }

//         vertices_count++;
//         temp = temp->next;
//     }
// }

// theta_renderable* theta_renderable_init_quad(const char* texture_filepath) {
//     THETA_PROFILE();

//     theta_renderable* renderable = INIT_STRUCT(theta_renderable);

//     theta_mesh_init(&renderable->mesh, g_quad_vertices, sizeof(g_quad_vertices) / sizeof(f32), 3, g_quad_indices, sizeof(g_quad_indices) / sizeof(u32), NULL, 0);
//     theta_shader_program_init_type(&renderable->program, THETA_SHADER_TYPE_BASIC_SHADER_TEXTURED);
//     renderable->material.uses_albedo = TRUE;
//     renderable->material.uses_color = FALSE;
//     renderable->material.albedo = theta_texture_init(texture_filepath);
//     theta_material_bind_to_shader(&renderable->material, &renderable->program);

//     return renderable;
// }

// theta_renderable* theta_renderable_init_quad_colored(theta_vector3f color) {
//     THETA_PROFILE();

//     theta_renderable* renderable = INIT_STRUCT(theta_renderable);

//     theta_mesh_init(&renderable->mesh, g_quad_vertices, sizeof(g_quad_vertices) / sizeof(f32), 3, g_quad_indices, sizeof(g_quad_indices) / sizeof(u32), NULL, 0);
//     theta_shader_program_init_type(&renderable->program, THETA_SHADER_TYPE_BASIC_SHADER_COLORED);
//     renderable->material.uses_albedo = FALSE;
//     renderable->material.uses_color = TRUE;
//     renderable->material.color = color;
//     theta_material_bind_to_shader(&renderable->material, &renderable->program);

//     return renderable;
// }

// theta_renderable* theta_renderable_init_cube(const char* texture_filepath, theta_texture_wrap_type wrap_type) {
//     THETA_PROFILE();

//     theta_renderable* renderable = INIT_STRUCT(theta_renderable);

//     theta_mesh_init(&renderable->mesh, g_cube_vertices, sizeof(g_cube_vertices) / sizeof(f32), 3, g_cube_indices, sizeof(g_cube_indices) / sizeof(u32), g_cube_normals, sizeof(g_cube_normals) / sizeof(f32));
//     theta_shader_program_init_type(&renderable->program, THETA_SHADER_TYPE_LIGHTING_SHADER_TEXTURED);
//     renderable->material.uses_albedo = TRUE;
//     renderable->material.uses_color = FALSE;
//     renderable->material.albedo = theta_texture_init(texture_filepath);
//     renderable->lighted = TRUE;
//     theta_material_bind_to_shader(&renderable->material, &renderable->program);

//     return renderable;
// }

// theta_renderable* theta_renderable_init_cube_colored(theta_vector3f color) {
//     THETA_PROFILE();

//     theta_renderable* renderable = INIT_STRUCT(theta_renderable);

//     theta_mesh_init(&renderable->mesh, g_cube_vertices, sizeof(g_cube_vertices) / sizeof(f32), 3, g_cube_indices, sizeof(g_cube_indices) / sizeof(u32), g_cube_normals, sizeof(g_cube_normals) / sizeof(f32));
//     theta_shader_program_init_type(&renderable->program, THETA_SHADER_TYPE_BASIC_SHADER_COLORED);
//     renderable->material.uses_albedo = FALSE;
//     renderable->material.uses_color = TRUE;
//     renderable->material.color = color;
//     theta_material_bind_to_shader(&renderable->material, &renderable->program);

//     return renderable;
// }

// theta_renderable* theta_renderable_init(const char* mesh_location, const char* texture_filepath, theta_texture_wrap_type wrap_type) {
//     theta_renderable* renderable = INIT_STRUCT(theta_renderable);

//     // TODO: Implement function
//     fastObjMesh* f_mesh = fast_obj_read(mesh_location);

//     THETA_ASSERT(f_mesh, "theta_renderable_init has failed. The reason being, fast obj failed to read the mesh");
    
    

//     return renderable;
// }

theta_renderable* theta_renderable_init(theta_mesh mesh, theta_material material, theta_shader_program shader_program) {
    THETA_PROFILE();

    theta_renderable* renderable = INIT_STRUCT(theta_renderable);

    renderable->material = material;
    renderable->mesh = mesh;
    renderable->program = shader_program;

    theta_material_bind_to_shader(&renderable->material, &renderable->program);

    return renderable;
}

void theta_renderable_destroy(theta_renderable* renderable) {
    THETA_PROFILE();

    renderable->mesh.destroy(&renderable->mesh);
}