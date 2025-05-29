#include "oglshader.h"

#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <string.h>
#include <glad/glad.h>
#include <math.h>

#include "renderer/material.h"

#include "renderer/texture.h"
#include "renderer/context/opengl/ogltexture.h"

static void tokenize_shader(const char* string, u32 max_length, char** v_source, char** f_source) {
    char* token = strtok(string, "\n");

    char* vertex_source = malloc(max_length * 2 * sizeof(char));
    char* fragment_source = malloc(max_length * 2 * sizeof(char));

    memset(vertex_source, 0, sizeof(max_length) * 2 * sizeof(char));
    memset(fragment_source, 0, sizeof(max_length) * 2 * sizeof(char));

    BOOL vertex_shader = TRUE;

    /*Get the vertex source and the fragment source SEPERATED*/
    while(token != NULL) {
        if(strcmp(token, "~NewShader") == 0) {
            vertex_shader = FALSE;
            token = strtok(NULL, "\n");
            continue;
        }

        if(vertex_shader) {
            if(token != NULL)
                strcat(vertex_source, token);
            strcat(vertex_source, "\n");
        }
        else {
            if(token != NULL)
                strcat(fragment_source, token);
            strcat(fragment_source, "\n");
        }

        token = strtok(NULL, "\n");
    }

    *v_source = vertex_source;
    *f_source = fragment_source;

}

static u32 compile_shader(u32 type, const char* src) {
    char shader_type_name[MAX_STRING] = "";

    (type == GL_VERTEX_SHADER) ? (strcat(shader_type_name, "Vertex Shader")) : (strcat(shader_type_name, "Fragment Shader"));

    u32 shaderID = glCreateShader(type);

    glShaderSource(shaderID, 1, &src, NULL);

    glCompileShader(shaderID);

    s32 compile_status = 0;

    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compile_status);

    if(!compile_status) {
        char message[1024];
        s32 log_length;

        glGetShaderInfoLog(shaderID, 1024, &log_length, message);

        THETA_ERROR("compile_shader for %s has failed. The reason being, OpenGL returned this error: %s\n", shader_type_name, message);
        return -1;
    }

    return shaderID;
}

static u32 create_and_link_program(u32 vertex_shader, u32 fragment_shader) {
    u32 program = glCreateProgram();

    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);

    glLinkProgram(program);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    s32 status = 0;

    glGetProgramiv(program, GL_LINK_STATUS, &status);

    if(!status) {
        char message[1024];
        s32 log_length;

        glGetProgramInfoLog(program, 1024, &log_length, message);

        THETA_ERROR("create_and_link_program has failed. The reason being, OpenGL returned this error: %s\n", message);
        return -1;
    }

    return program;
}

void theta_shader_program_init_opengl(theta_shader_program* program, const char* filename) {
    THETA_PROFILE();
    
    program->uninterpreted_data = malloc(sizeof(theta_shader_program_opengl_specifics));
    program->bound_textures_length = 0;
    
    u32 current_buffer_size = 1000;
    char* full_source = malloc(sizeof(char) * current_buffer_size);
    
    FILE* file = NULL;
    
    file = fopen(filename, "r");
    
    if(file == NULL) {
        THETA_ERROR("theta_shader_program_init_opengl has failed. The reason being, the shader program file that has been requested does not currently exist.\n");
    }

    char character;
    u32 length = 0;
    while((character = fgetc(file)) != EOF) {
        length++;
        
        if(length >= current_buffer_size) {
            current_buffer_size += 1000;
            full_source = realloc(full_source, current_buffer_size * sizeof(char));
        }
        
        full_source[length-1] = character;
    }
    full_source[length] = '\0';
    fclose(file);
    
    char* vsource;
    char* fsource;
    
    tokenize_shader(full_source, length, &vsource, &fsource);
    
    u32 vertex_shader = compile_shader(GL_VERTEX_SHADER, vsource);
    u32 fragment_shader = compile_shader(GL_FRAGMENT_SHADER, fsource);
    
    u32 programID = create_and_link_program(vertex_shader, fragment_shader);
    
    DATA_CAST(theta_shader_program_opengl_specifics, program)->programID = programID;
    
    free(vsource);
    free(fsource);
    free(full_source);

    /*Set Function Pointers*/

    program->set_mvp = &theta_shader_program_set_mvp_opengl;
    program->destroy = &theta_shader_program_destroy_opengl;
    program->give_material = &theta_shader_program_give_material_opengl;
    program->set_light = &theta_shader_program_set_light_opengl;
}

void theta_shader_program_set_mvp_opengl(theta_shader_program* program, mat4 model, mat4 view, mat4 projection) {
    theta_opengl_shader_program_bind_uniform_mat4f(program, "model", model);
    theta_opengl_shader_program_bind_uniform_mat4f(program, "view", view);
    theta_opengl_shader_program_bind_uniform_mat4f(program, "projection", projection);
}

void theta_shader_program_destroy_opengl(theta_shader_program* program) {
    THETA_PROFILE();
    
    glDeleteProgram(DATA_CAST(theta_shader_program_opengl_specifics, program)->programID);
}

// void theta_shader_program_set_directional_light_opengl(theta_shader_program* program, theta_light_directional light, vec3 viewing_position) {
//     // theta_opengl_shader_program_bind_uniform3f(program, "theta_SceneLightPos", light.transform.position);
//     // theta_opengl_shader_program_bind_uniform3f(program, "theta_SceneLightColor", light.light_color);
//     // theta_opengl_shader_program_bind_uniform3f(program, "theta_CameraViewingLocation", viewing_position);
//     theta_opengl_shader_program_bind_uniform3f(program, "theta_SceneDirectionalLight.specular", light.specular);
//     theta_opengl_shader_program_bind_uniform3f(program, "theta_SceneDirectionalLight.ambient", light.ambient);
//     theta_opengl_shader_program_bind_uniform3f(program, "theta_SceneDirectionalLight.diffuse", light.diffuse);
//     theta_opengl_shader_program_bind_uniform3f(program, "theta_SceneDirectionalLight.direction", light.direction);
//     theta_opengl_shader_program_bind_uniform3f(program, "theta_CameraViewingLocation", viewing_position);
//     theta_opengl_shader_program_bind_uniform1i(program, "theta_SceneDirectionalLightExists", TRUE);
// }

void theta_opengl_shader_program_bind_uniform1f(theta_shader_program* program, const char* name, f32 data) {
    theta_shader_program_opengl_specifics* self = DATA_CAST(theta_shader_program_opengl_specifics, program);
    
    s32 location = glGetUniformLocation(self->programID, name);

    if(location == -1) {
        THETA_WARN("theta_opengl_shader_program_bind_uniform1f has a warning. The reason being, either the shader you are using does not have a %s property, or it is just unused\n", name);
    }

    glUseProgram(self->programID);
    glUniform1f(location, data);
    glUseProgram(0);
}

void theta_opengl_shader_program_bind_uniform1i(theta_shader_program* program, const char* name, s32 data){
    theta_shader_program_opengl_specifics* self = DATA_CAST(theta_shader_program_opengl_specifics, program);
    
    s32 location = glGetUniformLocation(self->programID, name);

    if(location == -1) {
        THETA_WARN("theta_opengl_shader_program_bind_uniform1i has a warning. The reason being, either the shader you are using does not have a %s property, or it is just unused\n", name);
    }

    glUseProgram(self->programID);
    glUniform1i(location, data);
    glUseProgram(0);
}

void theta_opengl_shader_program_bind_uniform2f(theta_shader_program* program, const char* name, vec2 data) {
    theta_shader_program_opengl_specifics* self = DATA_CAST(theta_shader_program_opengl_specifics, program);
    
    s32 location = glGetUniformLocation(self->programID, name);

    if(location == -1) {
        THETA_WARN("theta_opengl_shader_program_bind_uniform2f has a warning. The reason being, either the shader you are using does not have a %s property, or it is just unused\n", name);
    }

    glUseProgram(self->programID);
    glUniform2fv(location, 1, data);
    glUseProgram(0);
}

void theta_opengl_shader_program_bind_uniform3f(theta_shader_program* program, const char* name, vec3 data) {
    theta_shader_program_opengl_specifics* self = DATA_CAST(theta_shader_program_opengl_specifics, program);
    
    s32 location = glGetUniformLocation(self->programID, name);

    if(location == -1) {
        THETA_WARN("theta_opengl_shader_program_bind_uniform3f has a warning. The reason being, either the shader you are using does not have a %s property, or it is just unused\n", name);
    }

    glUseProgram(self->programID);
    glUniform3fv(location, 1, data);
    glUseProgram(0);
}

void theta_opengl_shader_program_bind_uniform4f(theta_shader_program* program, const char* name, vec4 data) {
    theta_shader_program_opengl_specifics* self = DATA_CAST(theta_shader_program_opengl_specifics, program);
    
    s32 location = glGetUniformLocation(self->programID, name);

    if(location == -1) {
        THETA_WARN("theta_opengl_shader_program_bind_uniform4f has a warning. The reason being, either the shader you are using does not have a %s property, or it is just unused\n", name);
    }

    glUseProgram(self->programID);
    glUniform4fv(location, 1, data);
    glUseProgram(0);
}

void theta_opengl_shader_program_bind_uniform_mat4f(theta_shader_program* program, const char* name, mat4 data) {
    theta_shader_program_opengl_specifics* self = DATA_CAST(theta_shader_program_opengl_specifics, program);
    
    s32 location = glGetUniformLocation(self->programID, name);

    if(location == -1) {
        THETA_WARN("theta_opengl_shader_program_bind_uniform_mat4f has a warning. The reason being, either the shader you are using does not have a %s property, or it is just unused\n", name);
    }

    glUseProgram(self->programID);
    glUniformMatrix4fv(location, 1, GL_FALSE, data[0]);
    glUseProgram(0);
}

void theta_shader_program_give_material_opengl(theta_shader_program* program, struct theta_material* material) {
    theta_shader_program_opengl_specifics* self = DATA_CAST(theta_shader_program_opengl_specifics, program);
    
    /*Fill out the color information of the shader*/
    theta_opengl_shader_program_bind_uniform1i(program, "theta_UsesAlbedoMap", FALSE);
    if(material->albedo != NULL) {
        theta_opengl_shader_program_bind_uniform1i(program, "theta_UsesAlbedoMap", TRUE);
        theta_opengl_shader_program_bind_uniform1i(program, "theta_Albedo", program->bound_textures_length);
        program->bound_textures[program->bound_textures_length] = material->albedo;
        
        program->bound_textures_length++;
    }


    if(material->uses_color) {
        //vec4 color = {material->color[0], material->color[1], material->color[2], 1.0f};
        theta_opengl_shader_program_bind_uniform3f(program, "theta_AlbedoColor", material->color);
    }

    // If the material has lighting properties attached to it, fill out the lighting properties.
    if(material->lighted) {
        theta_opengl_shader_program_bind_uniform1f(program, "theta_MetallicScalar", material->metallic);
        theta_opengl_shader_program_bind_uniform1f(program, "theta_RoughnessScalar", material->roughness);
        theta_opengl_shader_program_bind_uniform1f(program, "theta_AmbientOcclusionScalar", material->ao);
        
        
        theta_opengl_shader_program_bind_uniform1i(program, "theta_UsesMetallicMap", FALSE);
        theta_opengl_shader_program_bind_uniform1i(program, "theta_UsesNormalMap", FALSE);
        theta_opengl_shader_program_bind_uniform1i(program, "theta_UsesRoughnessMap", FALSE);
        theta_opengl_shader_program_bind_uniform1i(program, "theta_UsesAmbientOcclusionMap", FALSE);

        if(material->metallic_map != NULL) {
            theta_opengl_shader_program_bind_uniform1i(program, "theta_UsesMetallicMap", TRUE);
            theta_opengl_shader_program_bind_uniform1i(program, "theta_Metallic", program->bound_textures_length);
            program->bound_textures[program->bound_textures_length] = material->metallic_map;
            program->bound_textures_length++;
        }

        if(material->normal_map != NULL) {
            theta_opengl_shader_program_bind_uniform1i(program, "theta_UsesNormalMap", TRUE);
            theta_opengl_shader_program_bind_uniform1i(program, "theta_Normal", program->bound_textures_length);
            program->bound_textures[program->bound_textures_length] = material->normal_map;
            program->bound_textures_length++;
        }

        if(material->roughness_map != NULL) {
            theta_opengl_shader_program_bind_uniform1i(program, "theta_UsesRoughnessMap", TRUE);
            theta_opengl_shader_program_bind_uniform1i(program, "theta_Roughness", program->bound_textures_length);
            program->bound_textures[program->bound_textures_length] = material->roughness_map;
            program->bound_textures_length++;
        }

        if(material->ao_map != NULL) {
            theta_opengl_shader_program_bind_uniform1i(program, "theta_UsesAmbientOcclusionMap", TRUE);
            theta_opengl_shader_program_bind_uniform1i(program, "theta_AmbientOcclusion", program->bound_textures_length);
            program->bound_textures[program->bound_textures_length] = material->ao_map;
            program->bound_textures_length++;
        }
    }

    // Texture tiling
    theta_opengl_shader_program_bind_uniform1f(program, "xTiling", material->texture_tiling_x);
    theta_opengl_shader_program_bind_uniform1f(program, "yTiling", material->texture_tiling_y);
}

void theta_shader_program_set_light_opengl(theta_shader_program* program, theta_light* lights, u32 light_count, vec3 viewing_position) {
    theta_opengl_shader_program_bind_uniform3f(program, "theta_CameraViewingLocation", viewing_position);

    theta_opengl_shader_program_bind_uniform3f(program, "theta_FirstLight.Position", lights[0].location);
    theta_opengl_shader_program_bind_uniform3f(program, "theta_FirstLight.Color", lights[0].color);
    theta_opengl_shader_program_bind_uniform1f(program, "theta_FirstLight.Intensity", lights[0].intensity);
}