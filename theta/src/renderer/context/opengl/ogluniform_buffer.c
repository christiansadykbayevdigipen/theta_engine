#include "ogluniform_buffer.h"

#include <malloc.h>

#include <glad/glad.h>

#include <string.h>

void theta_uniform_buffer_init_opengl(theta_uniform_buffer* buffer, u64 data_size, const char* associated_name) {
    buffer->uninterpreted_data = malloc(sizeof(theta_uniform_buffer_opengl_specifics));
    buffer->data_size = data_size;
    strcpy(buffer->name, associated_name);

    AUTO_SELF(theta_uniform_buffer_opengl_specifics, buffer);

    glGenBuffers(1, &self->id);
    
    glBindBuffer(GL_UNIFORM_BUFFER, self->id);
    glBufferData(GL_UNIFORM_BUFFER, data_size, NULL, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    // Function Pointers
    buffer->update_data = &theta_uniform_buffer_update_data_opengl;
}

void theta_uniform_buffer_update_data_opengl(theta_uniform_buffer* buffer, void* data) {
    AUTO_SELF(theta_uniform_buffer_opengl_specifics, buffer);

    glBindBuffer(GL_UNIFORM_BUFFER, self->id);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, buffer->data_size, data);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}