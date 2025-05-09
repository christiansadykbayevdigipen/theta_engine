#include "ogltexture.h"

#include <malloc.h>
#include <memory.h>

#include <glad/gl.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

void theta_texture_init_opengl(theta_texture* texture, const char* filepath) {
    texture->uninterpreted_data = malloc(sizeof(theta_texture_opengl_specifics));

    theta_texture_opengl_specifics* self = DATA_CAST(theta_texture_opengl_specifics, texture);

    u32 width, height, nrChannels;

    u8* data = stbi_load(filepath, &width, &height, &nrChannels, 0);

    THETA_ASSERT(data, "theta_texture_init_opengl has failed. The reason being, filepath does not exist for texture");

    glGenTextures(1, &self->texture_id);
    glBindTexture(GL_TEXTURE_2D, self->texture_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);   
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);   
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(data); 
}