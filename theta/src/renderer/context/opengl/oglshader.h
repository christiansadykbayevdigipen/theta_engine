#pragma once 

#include "renderer/shader.h"

struct theta_texture;

typedef struct {
    u32 programID;
    u32 albedo_unit_id;
}theta_shader_program_opengl_specifics;

THETA_API void theta_shader_program_init_opengl(theta_shader_program* program, const char* filename);

THETA_API void theta_shader_program_set_mvp_opengl(theta_shader_program* program, mat4 model, mat4 view, mat4 projection);

THETA_API void theta_shader_program_destroy_opengl(theta_shader_program* program);

THETA_API void theta_shader_program_give_albedo_opengl(theta_shader_program* program, struct theta_texture* albedo_texture);

THETA_API void theta_shader_program_set_color_opengl(theta_shader_program* program, vec3 color);

THETA_API void theta_shader_program_set_light_opengl(theta_shader_program* program, theta_light_descriptor light, vec3 viewing_position);

THETA_API void theta_shader_program_set_ambient_light_opengl(theta_shader_program* program, theta_light_ambient_descriptor light);

THETA_API void theta_shader_program_set_specular_opengl(theta_shader_program* program, f32 specular_strength);

THETA_API void theta_shader_program_set_specular_highlight_opengl(theta_shader_program* program, f32 specular_highlight);