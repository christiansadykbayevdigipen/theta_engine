#pragma once

#include "core.h"
#include <cglm/cglm.h>
#include "object/light.h"

struct theta_texture;

typedef enum {
    THETA_SHADER_TYPE_BASIC_SHADER_TEXTURED,
    THETA_SHADER_TYPE_BASIC_SHADER_COLORED,
    THETA_SHADER_TYPE_LIGHTING_SHADER_TEXTURED
}theta_shader_type;

typedef struct theta_shader_program{
    void* uninterpreted_data;
    void (*set_mvp)(struct theta_shader_program* program, mat4 model, mat4 view, mat4 projection);
    void (*destroy)(struct theta_shader_program* program);
    void (*give_albedo)(struct theta_shader_program* program, struct theta_texture* albedo);
    void (*set_color)(struct theta_shader_program* program, vec3 color);
    void (*set_light)(struct theta_shader_program* program, theta_light_descriptor light, vec3 viewing_position);
    void (*set_ambient_light)(struct theta_shader_program* program, theta_light_ambient_descriptor light);
    void (*set_specular)(struct theta_shader_program* program, f32 specular_strength);
    void (*set_specular_highlight)(struct theta_shader_program* program, f32 specular_highlight);
    struct theta_texture* albedo_texture;
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