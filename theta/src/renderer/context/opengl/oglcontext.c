#include "oglcontext.h"

#include <memory.h>
#include <malloc.h>

#include <glad/gl.h>

#include "window/platform/shared/shared_window.h"
#include "oglshader.h"

void theta_rendering_context_init_opengl(theta_rendering_context* ctx, theta_window* window) {
    THETA_PROFILE();
    ctx->uninterpreted_data = malloc(sizeof(theta_opengl_rendering_context_specifics));
    ctx->window = window;
    ctx->api = THETA_API_OPENGL;
    ctx->clear = &theta_rendering_context_clear_opengl;
    ctx->swap = &theta_rendering_context_swap_opengl;
    ctx->destroy = &theta_rendering_context_destroy_opengl;
    
    THETA_ASSERT(gladLoadGL(theta_shared_window_get_proc_address(window)), "theta_rendering_context_init_opengl has failed. The reason being, glad, the opengl loader, has failed to load opengl.");
}

void theta_rendering_context_clear_opengl(theta_rendering_context* ctx) {
    glClear(GL_COLOR_BUFFER_BIT);
}

void theta_rendering_context_swap_opengl(theta_rendering_context* ctx) {
#if defined(THETA_PLATFORM_SHARED)
    theta_shared_window_swap_buffers(ctx->window);
#endif
}

void theta_rendering_context_vao_init(theta_rendering_context* ctx, theta_opengl_vertex_array* vao) {
    glGenVertexArrays(1, &vao->vertex_array_id);
    vao->current_layout_length = 0;
}

void theta_rendering_context_vbo_init(theta_rendering_context* ctx, theta_opengl_vertex_buffer* vbo, f32* vertices, u32 size) {
    glGenBuffers(1, &vbo->vertex_buffer_id);

    glBindBuffer(GL_ARRAY_BUFFER, vbo->vertex_buffer_id);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void theta_rendering_context_vao_push_vbo(theta_rendering_context* ctx, theta_opengl_vertex_array* vao, theta_opengl_vertex_buffer* vbo, theta_opengl_vao_layout layout) {
    glBindBuffer(GL_ARRAY_BUFFER, vbo->vertex_buffer_id);

    glBindVertexArray(vao->vertex_array_id);
    
    glVertexAttribPointer(layout.index, layout.dimension, GL_FLOAT, GL_FALSE, layout.stride, (const void*)(layout.offset));
    
    glBindVertexArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    vao->layout[vao->current_layout_length] = layout;

    vao->current_layout_length++;
}

void theta_rendering_context_vao_draw(theta_rendering_context* ctx, theta_opengl_vertex_array* vao, u32 vertex_count, theta_shader_program* associated_shader) {
    glUseProgram(DATA_CAST(theta_shader_program_opengl_specifics, associated_shader)->programID);
    
    glBindVertexArray(vao->vertex_array_id);
    
    for(u32 i = 0; i < vao->current_layout_length; i++) {
        glEnableVertexAttribArray(i);
    }

    glDrawArrays(GL_TRIANGLES, 0, vertex_count);

    for(u32 i = 0; i < vao->current_layout_length; i++) {
        glDisableVertexAttribArray(i);
    }
    
    glBindVertexArray(0);
    glUseProgram(0);
}

void theta_rendering_context_vao_destroy(theta_rendering_context* ctx, theta_opengl_vertex_array* vao) {
    glDeleteVertexArrays(1, &vao->vertex_array_id);
}

void theta_rendering_context_vbo_destroy(theta_rendering_context* ctx, theta_opengl_vertex_buffer* vbo) {
    glDeleteBuffers(1, &vbo->vertex_buffer_id);
}

void theta_rendering_context_destroy_opengl(theta_rendering_context* ctx) {

}