#pragma once

#include "core.h"
#include <cglm/cglm.h>
#include "object/light.h"

struct theta_texture;
struct theta_material;

typedef enum {
    THETA_SHADER_TYPE_BASIC_SHADER_TEXTURED,
    THETA_SHADER_TYPE_BASIC_SHADER_COLORED,
    THETA_SHADER_TYPE_LIGHTING_SHADER_TEXTURED
}theta_shader_type;

typedef struct theta_shader_program{
    void* uninterpreted_data;
    void (*set_mvp)(struct theta_shader_program* program, mat4 model, mat4 view, mat4 projection);
    void (*destroy)(struct theta_shader_program* program);
    void (*give_material)(struct theta_shader_program* program, struct theta_material* material);
    void (*set_light)(struct theta_shader_program* program, theta_light* lights, u32 light_count, vec3 viewing_position);
    struct theta_texture* bound_textures[10];
    u32 bound_textures_length;
    void (*give_uniform1f)(struct theta_shader_program* program, const char* name, f32 data);
    void (*give_uniform1i)(struct theta_shader_program* program, const char* name, s32 data);
    void (*give_uniform2f)(struct theta_shader_program* program, const char* name, vec2 data);
    void (*give_uniform3f)(struct theta_shader_program* program, const char* name, vec3 data);
    void (*give_uniform4f)(struct theta_shader_program* program, const char* name, vec4 data);
    void (*give_uniform_mat4f)(struct theta_shader_program* program, const char* name, mat4 data);
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