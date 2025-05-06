#pragma once

#include "core.h"
#include "renderer/context/context.h"

#define MAX_VAO_LAYOUT 20

typedef struct {
    u32 proc_address;
}theta_opengl_rendering_context_specifics;

/*
@brief Describes how a certain Vertex Buffer should be layed out in a Vertex Array Object.
@param dimension The size of the vertex position. Is it three or two dimensional?
@param offset The offset to get to the vertex position.
@param stride How many bytes it takes to get to the next vertex position
@param index The index in the VAO object.
*/
typedef struct {
    u32 dimension;
    u32 offset;
    u32 stride;
    u32 index;
}theta_opengl_vao_layout;

typedef struct {
    u32 vertex_buffer_id;
}theta_opengl_vertex_buffer;

typedef struct {
    u32 vertex_array_id;
    theta_opengl_vao_layout layout[MAX_VAO_LAYOUT];
    u32 current_layout_length;
}theta_opengl_vertex_array;

THETA_API void theta_rendering_context_init_opengl(theta_rendering_context* ctx, theta_window* window);

THETA_API void theta_rendering_context_clear_opengl(theta_rendering_context* ctx);
THETA_API void theta_rendering_context_swap_opengl(theta_rendering_context* ctx);

/*
@brief Initializes a Vertex Array Object
@param ctx
@param vao A pointer to an uninitialized VAO object
*/
THETA_API void theta_rendering_context_vao_init(theta_rendering_context* ctx, theta_opengl_vertex_array* vao);


/*
@brief Initializes a Vertex Buffer Object
@param ctx
@param vbo A pointer to an uninitialized VBO object
@param vertices The array of vertices
@param size The size (in bytes) of the array
*/
THETA_API void theta_rendering_context_vbo_init(theta_rendering_context* ctx, theta_opengl_vertex_buffer* vbo, f32* vertices, u32 size);

/*
@brief Pushes a Vertex Buffer Object into a Vertex Array Object.
@param ctx 
@param A pointer to an initialized VAO object.
@param A pointer to an initialized VBO object.
@param layout How the VBO should be treated in the VAO. Denotes the size of each vertex position, the stride (how many bytes it takes to get to the next position), the offset (how many bytes it takes to get to the position from the beginning), and index, which is just an identifier. Because you can have multiple VBOs in a VAO.
*/
THETA_API void theta_rendering_context_vao_push_vbo(theta_rendering_context* ctx, theta_opengl_vertex_array* vao, theta_opengl_vertex_buffer* vbo, theta_opengl_vao_layout layout);

/*
@brief Draws a particular vertex array (without an Index Buffer)
@param vertex_count The number of whole vertex positions.
*/
THETA_API void theta_rendering_context_vao_draw(theta_rendering_context* ctx, theta_opengl_vertex_array* vao, u32 vertex_count);