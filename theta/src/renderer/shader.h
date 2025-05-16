#pragma once

#include "core.h"
#include "math/tmath.h"

struct theta_texture;

typedef enum {
    THETA_SHADER_TYPE_BASIC_SHADER_TEXTURED,
    THETA_SHADER_TYPE_BASIC_SHADER_COLORED
}theta_shader_type;

/*
@brief This is the typical information that is sent into the uniform/constant buffer area in the shader. This is set to VS_INPUT in HLSL or uniform struct is GLSL.
*/
typedef struct {
    theta_mat4x4f projection;
    theta_mat4x4f view;
    theta_mat4x4f model;
    theta_vector3f color;
}theta_program_uniform;

typedef struct theta_shader_program{
    void* uninterpreted_data;
    void (*set_mvp)(struct theta_shader_program* program, theta_mat4x4f model, theta_mat4x4f view, theta_mat4x4f projection);
    void (*destroy)(struct theta_shader_program* program);
    void (*give_albedo)(struct theta_shader_program* program, const char* filepath);
    void (*set_color)(struct theta_shader_program* program, theta_vector3f color);

    struct theta_texture* tex;
}theta_shader_program;

/*
@brief Initializes a shader program for theta.
@param program A pointer to an uninitialized theta_shader_program structure
@param filename The location of the full shader program with both Pixel and Vertex shaders mixed together.
*/
THETA_API void theta_shader_program_init(theta_shader_program* program, const char* filename);

/*
@brief Initializes a shader program for theta.
@param program A pointer to an uninitialized theta_shader_program structure
@param type The type of default shader to give to theta. Theta has a shader bank of default shaders.
*/
THETA_API void theta_shader_program_init_type(theta_shader_program* program, theta_shader_type type);