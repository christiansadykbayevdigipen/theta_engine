#pragma once 

#include "renderer/shader.h"

struct theta_texture;

typedef struct {
    u32 programID;
    u32 albedo_unit_id;
}theta_shader_program_opengl_specifics;

THETA_API void theta_shader_program_init_opengl(theta_shader_program* program, const char* filename);

THETA_API void theta_shader_program_set_mvp_opengl(theta_shader_program* program, theta_mat4x4f model, theta_mat4x4f view, theta_mat4x4f projection);

THETA_API void theta_shader_program_destroy_opengl(theta_shader_program* program);

THETA_API void theta_shader_program_give_albedo_opengl(theta_shader_program* program, struct theta_texture* albedo_texture);

THETA_API void theta_shader_program_set_color_opengl(theta_shader_program* program, theta_vector3f color);

THETA_API void theta_shader_program_set_light_position_opengl(theta_shader_program* program, theta_vector3f location);