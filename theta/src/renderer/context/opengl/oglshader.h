#pragma once 

#include "renderer/shader.h"

struct theta_texture;

typedef struct {
    u32 programID;
    u32 ubos_associated_block_indices[MAX_UBO_COUNT];
}theta_shader_program_opengl_specifics;

THETA_API void theta_shader_program_init_opengl(theta_shader_program* program, const char* filename);

THETA_API void theta_shader_program_set_mvp_opengl(theta_shader_program* program, mat4 model, mat4 view, mat4 projection);

THETA_API void theta_shader_program_destroy_opengl(theta_shader_program* program);

// THETA_API void theta_shader_program_give_albedo_opengl(theta_shader_program* program, struct theta_texture* albedo_texture);

// THETA_API void theta_shader_program_set_color_opengl(theta_shader_program* program, vec3 color);

THETA_API void theta_shader_program_set_light_opengl(theta_shader_program* program, theta_light* lights, u32 light_count, vec3 viewing_position);


THETA_API void theta_shader_program_bind_uniform1f_opengl(theta_shader_program* program, const char* name, f32 data);
THETA_API void theta_shader_program_bind_uniform1i_opengl(theta_shader_program* program, const char* name, s32 data);
THETA_API void theta_shader_program_bind_uniform2f_opengl(theta_shader_program* program, const char* name, vec2 data);
THETA_API void theta_shader_program_bind_uniform3f_opengl(theta_shader_program* program, const char* name, vec3 data);
THETA_API void theta_shader_program_bind_uniform4f_opengl(theta_shader_program* program, const char* name, vec4 data);
THETA_API void theta_shader_program_bind_uniform_mat4f_opengl(theta_shader_program* program, const char* name, mat4 data);
THETA_API void theta_shader_program_give_uniform_buffer_opengl(theta_shader_program* program, theta_uniform_buffer buffer);

THETA_API void theta_shader_program_give_material_opengl(theta_shader_program* program, struct theta_material* material);

// THETA_API void theta_shader_program_set_specular_opengl(theta_shader_program* program, f32 specular_strength);

// THETA_API void theta_shader_program_set_specular_highlight_opengl(theta_shader_program* program, f32 specular_highlight);