#include "oglskybox.h"

#include "oglshader.h"

#include <glad/glad.h>

#include <stb_image.h>

#include "renderer/renderer.h"
#include "oglcontext.h"
#include "oglmesh.h"

#include <memory.h>
#include <malloc.h>

// https://learnopengl.com/Advanced-OpenGL/Cubemaps

static f32 g_cubemap_vertices[] = {
    // positions          
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    -1.0f,  1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f,  1.0f
};

void theta_skybox_init_opengl(theta_skybox* skybox, char texture_locations[6][MAX_STRING]) {
    // Basic member initialization
    skybox->uninterpreted_data = malloc(sizeof(theta_skybox_opengl_specifics));
    memset(skybox->uninterpreted_data, 0, sizeof(theta_skybox_opengl_specifics));
    theta_skybox_opengl_specifics* self = DATA_CAST(theta_skybox_opengl_specifics, skybox);
    
    theta_mesh_init(&skybox->cubemap_mesh, g_cubemap_vertices, sizeof(g_cubemap_vertices) / sizeof(g_cubemap_vertices[0]), 3, NULL, 0, NULL, 0, NULL, 0);

    // Texture Creating time.
    glGenTextures(1, &self->texture_id);
    glBindTexture(GL_TEXTURE_CUBE_MAP, self->texture_id);

    stbi_set_flip_vertically_on_load(0);

    u32 width, height, nr_channels;
    const u32 number_of_textures = 6;
    for(u32 i = 0; i < number_of_textures; i++) { 
        u8* data = stbi_load(texture_locations[i], &width, &height, &nr_channels, 3);
        THETA_ASSERT(data, "theta_skybox_init_opengl has failed. The reason being, at least one of the textures has an invalid filepath");

        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

        stbi_image_free(data);
    }
    stbi_set_flip_vertically_on_load(1);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

    // Shader creating time
    theta_shader_program_init(&skybox->program, "res/skybox.shader");
    
    // TODO: Maybe abstract this a bit? 
    theta_opengl_shader_program_bind_uniform1f(&skybox->program, "theta_Skybox", 0);

    skybox->render = &theta_skybox_render_opengl;
    skybox->bind_vp = &theta_skybox_bind_vp_opengl;
}

void theta_skybox_render_opengl(theta_skybox* skybox) {
    theta_skybox_opengl_specifics* self = DATA_CAST(theta_skybox_opengl_specifics, skybox);
    theta_mesh_opengl_specifics* mesh = (theta_mesh_opengl_specifics*)skybox->uninterpreted_data;

    theta_rendering_context* ctx = theta_renderer_get_context();
    theta_rendering_context_vao_draw_skybox(ctx, &mesh->vao, skybox->cubemap_mesh.vertex_position_count, &skybox->program, self->texture_id);
}

void theta_skybox_bind_vp_opengl(theta_skybox* skybox, mat4 view, mat4 projection) {
    mat4 newview;
    glm_mat4_copy(view, newview);

    newview[3][0] = 0.0f;
    newview[3][1] = 0.0f;
    newview[3][2] = 0.0f;

    theta_opengl_shader_program_bind_uniform_mat4f(&skybox->program, "view", newview);
    theta_opengl_shader_program_bind_uniform_mat4f(&skybox->program, "projection", projection);
}