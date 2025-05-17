#include "ogltexture.h"

#include <malloc.h>
#include <memory.h>

#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

theta_texture* theta_texture_init_opengl(const char* filepath) {
    THETA_PROFILE();
    return theta_texture_initw_opengl(filepath, THETA_TEXTURE_WRAP_TYPE_REPEAT);
}

theta_texture* theta_texture_initw_opengl(const char* filepath, theta_texture_wrap_type wrap_type) {
    THETA_PROFILE();
    theta_texture* texture = INIT_STRUCT(theta_texture);

    texture->uninterpreted_data = malloc(sizeof(theta_texture_opengl_specifics));

    theta_texture_opengl_specifics* self = DATA_CAST(theta_texture_opengl_specifics, texture);

    u32 width, height, nrChannels;
    stbi_set_flip_vertically_on_load(TRUE);

    u8* data = stbi_load(filepath, &width, &height, &nrChannels, 4);

    THETA_ASSERT(data, "theta_texture_init_opengl has failed. The reason being, filepath does not exist for texture");

    glGenTextures(1, &self->texture_id);
    glBindTexture(GL_TEXTURE_2D, self->texture_id);

    u32 wrap_type_ogl = GL_REPEAT;

    switch(wrap_type) {
    case THETA_TEXTURE_WRAP_TYPE_REPEAT:
        wrap_type_ogl = GL_REPEAT;
        break;
    case THETA_TEXTURE_WRAP_TYPE_MIRROR_CLAMP_TO_EDGE:
        wrap_type_ogl = GL_MIRROR_CLAMP_TO_EDGE;
        break;
    case THETA_TEXTURE_WRAP_TYPE_MIRROR:
        wrap_type_ogl = GL_MIRRORED_REPEAT;
        break;
    case THETA_TEXTURE_WRAP_TYPE_CLAMP:
        wrap_type_ogl = GL_CLAMP;
        break;
    default:
        THETA_WARN("theta_texture_initw_opengl has an issue. The reason being, the texture wrap type given to this method does not exist! Defaulting to repeat\n");
        break;
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_type_ogl);   
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_type_ogl);   
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);   
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //u32 default_format = GL_RGB;

    // if(nrChannels > 3)
    //     default_format = GL_RGBA;

    u32 default_format = GL_RGBA;

    glTexImage2D(GL_TEXTURE_2D, 0, default_format, width, height, 0, default_format, GL_UNSIGNED_BYTE, data);

    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(data); 

    return texture;
}