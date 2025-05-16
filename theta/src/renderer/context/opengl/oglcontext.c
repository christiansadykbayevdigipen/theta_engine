#include "oglcontext.h"

#include <memory.h>
#include <malloc.h>

#include <glad/glad.h>

#include "window/platform/shared/shared_window.h"
#include "oglshader.h"
#include "ogltexture.h"

#include <string.h>

//https://learnopengl.com/In-Practice/Debugging
GLenum glCheckError_(const char *file, int line)
{
    GLenum errorCode;
    while ((errorCode = glGetError()) != GL_NO_ERROR)
    {
        char error[256];
        memset(error, 0, sizeof(char) * 256);
        switch (errorCode)
        {
            case GL_INVALID_ENUM:                  strcat(error, "INVALID_ENUM"); break;
            case GL_INVALID_VALUE:                 strcat(error, "INVALID_VALUE"); break;
            case GL_INVALID_OPERATION:             strcat(error, "INVALID_OPERATION"); break;
            case GL_STACK_OVERFLOW:                strcat(error, "STACK_OVERFLOW"); break;
            case GL_STACK_UNDERFLOW:               strcat(error, "STACK_UNDERFLOW"); break;
            case GL_OUT_OF_MEMORY:                 strcat(error, "OUT_OF_MEMORY"); break;
            case GL_INVALID_FRAMEBUFFER_OPERATION: strcat(error, "INVALID_FRAMEBUFFER_OPERATION"); break;
        }
        printf("%s | %s (%s)\n", error, file, line);
    }
    return errorCode;
}
#define glCheckError() glCheckError_(__FILE__, __LINE__) 

theta_rendering_context* theta_rendering_context_init_opengl(theta_window* window) {
    THETA_PROFILE();
    theta_rendering_context* ctx = INIT_STRUCT(theta_rendering_context);

    ctx->uninterpreted_data = malloc(sizeof(theta_opengl_rendering_context_specifics));
    ctx->window = window;
    ctx->api = THETA_API_OPENGL;
    ctx->clear = &theta_rendering_context_clear_opengl;
    ctx->swap = &theta_rendering_context_swap_opengl;
    ctx->destroy = &theta_rendering_context_destroy_opengl;
    
    THETA_ASSERT(gladLoadGL(), "theta_rendering_context_init_opengl has failed. The reason being, glad, the opengl loader, has failed to load opengl.");

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    return ctx;
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

void theta_rendering_context_vao_draw(theta_rendering_context* ctx, theta_opengl_vertex_array* vao, u32 vertex_count, theta_shader_program* associated_shader, theta_opengl_index_buffer* ibo) {
    glUseProgram(DATA_CAST(theta_shader_program_opengl_specifics, associated_shader)->programID);
    
    glBindVertexArray(vao->vertex_array_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo->index_buffer_id);
    
    for(u32 i = 0; i < vao->current_layout_length; i++) {
        glEnableVertexAttribArray(i);
    }

    if(associated_shader->tex != NULL) {
        theta_shader_program_opengl_specifics* shader_spec = DATA_CAST(theta_shader_program_opengl_specifics, associated_shader);
        theta_texture_opengl_specifics* tex_spec = DATA_CAST(theta_texture_opengl_specifics, associated_shader->tex);

        glActiveTexture(GL_TEXTURE0 + shader_spec->albedo_unit_id);
        glBindTexture(GL_TEXTURE_2D, tex_spec->texture_id);
    }

    glDrawElements(GL_TRIANGLES, ibo->indices_count, GL_UNSIGNED_INT, NULL);

    if(associated_shader->tex != NULL) {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    for(u32 i = 0; i < vao->current_layout_length; i++) {
        glDisableVertexAttribArray(i);
    }
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
    glBindVertexArray(0);
    glUseProgram(0);
}

void theta_rendering_context_vao_destroy(theta_rendering_context* ctx, theta_opengl_vertex_array* vao) {
    glDeleteVertexArrays(1, &vao->vertex_array_id);
}

void theta_rendering_context_vbo_destroy(theta_rendering_context* ctx, theta_opengl_vertex_buffer* vbo) {
    glDeleteBuffers(1, &vbo->vertex_buffer_id);
}

void theta_rendering_context_ibo_init(theta_rendering_context* ctx, theta_opengl_index_buffer* ibo, u32* indices, u32 index_count) {
    ibo->indices_count = index_count;  
    
    glGenBuffers(1, &ibo->index_buffer_id);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo->index_buffer_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_count * sizeof(u32), indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void theta_rendering_context_destroy_opengl(theta_rendering_context* ctx) {
    THETA_PROFILE();

    free(ctx->uninterpreted_data);
    free(ctx);
}