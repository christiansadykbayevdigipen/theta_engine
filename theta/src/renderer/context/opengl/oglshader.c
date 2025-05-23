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

        THETA_FATAL("compile_shader for %s has failed. The reason being, OpenGL returned this error: %s\n", shader_type_name, message);
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

        THETA_FATAL("create_and_link_program has failed. The reason being, OpenGL returned this error: %s\n", message);
        return -1;
    }

    return program;
}

void theta_shader_program_init_opengl(theta_shader_program* program, const char* filename) {
    THETA_PROFILE();
    
    program->uninterpreted_data = malloc(sizeof(theta_shader_program_opengl_specifics));
    program->albedo_texture = NULL;
    
    u32 current_buffer_size = 1000;
    char* full_source = malloc(sizeof(char) * current_buffer_size);
    
    FILE* file = NULL;
    
    file = fopen(filename, "r");
    
    THETA_ASSERT(file != NULL, "theta_shader_program_init_opengl has failed. The reason being, the shader program file that has been requested does not currently exist.");
    
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
    program->set_light = &theta_shader_program_set_light_opengl;
    program->set_ambient_light = &theta_shader_program_set_ambient_light_opengl;
    program->give_material = &theta_shader_program_give_material_opengl;
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

// void theta_shader_program_give_albedo_opengl(theta_shader_program* program, theta_texture* albedo_texture) {
//     THETA_PROFILE();
//     theta_shader_program_opengl_specifics* progspec = DATA_CAST(theta_shader_program_opengl_specifics, program);

//     program->albedo_texture = albedo_texture;

//     glUseProgram(progspec->programID);

//     DATA_CAST(theta_shader_program_opengl_specifics, program)->albedo_unit_id = 0;

//     s32 loc = glGetUniformLocation(progspec->programID, "theta_Albedo");

//     if(loc == -1) {
//         THETA_WARN("theta_shader_program_give_albedo_opengl has failed. The reason being, the shader you are using does not have a proper albedo texture property! Be sure that there is a Uniform Sampler2D called 'theta_Albedo' in your vertex shader!\n");
//         return;
//     }

//     glUniform1i(loc, progspec->albedo_unit_id);
    
//     glUseProgram(0);
// }

// void theta_shader_program_set_color_opengl(theta_shader_program* program, vec3 color) {
//     theta_shader_program_opengl_specifics* self = DATA_CAST(theta_shader_program_opengl_specifics, program);

//     s32 location = glGetUniformLocation(self->programID, "color");

//     //THETA_ASSERT(location == -1, "");
//     if(location == -1) {
//         THETA_WARN("theta_shader_program_set_color_opengl has failed. The reason being, the shader that you are using does not have a uniform vec4 named 'color'!\n");
//         return;
//     }

//     glUseProgram(self->programID);

//     glUniform4f(location, color[0], color[1], color[2], 1.0f);
    
//     glUseProgram(0);
// }

void theta_shader_program_set_light_opengl(theta_shader_program* program, theta_light_descriptor light, vec3 viewing_position) {
    theta_opengl_shader_program_bind_uniform3f(program, "theta_SceneLightPos", light.transform.position);
    theta_opengl_shader_program_bind_uniform3f(program, "theta_SceneLightColor", light.light_color);
    theta_opengl_shader_program_bind_uniform3f(program, "theta_CameraViewingLocation", viewing_position);
}

void theta_shader_program_set_ambient_light_opengl(theta_shader_program* program, theta_light_ambient_descriptor light) {
    theta_opengl_shader_program_bind_uniform1f(program, "theta_AmbientStrength", light.ambient_strength);
    theta_opengl_shader_program_bind_uniform3f(program, "theta_AmbientColor", light.light_color);
}

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
    if(material->uses_albedo) {
        self->albedo_unit_id = 0;
        theta_opengl_shader_program_bind_uniform1f(program, "theta_Albedo", self->albedo_unit_id);
        program->albedo_texture = material->albedo;
    }
    if(material->uses_color) {
        vec4 color = {material->color[0], material->color[1], material->color[2], 1.0f};
        theta_opengl_shader_program_bind_uniform4f(program, "color", color);
    }

    // If the material has lighting properties attached to it, fill out the lighting properties.
    if(material->lighted) {
        theta_opengl_shader_program_bind_uniform1f(program, "theta_MaterialSpecularStrength", material->specular_strength);
        theta_opengl_shader_program_bind_uniform1f(program, "theta_MaterialSpecularHighlight", material->specular_highlight);
    }
}

// void theta_shader_program_set_specular_opengl(theta_shader_program* program, f32 specular_strength) {
//     theta_shader_program_opengl_specifics* self = DATA_CAST(theta_shader_program_opengl_specifics, program);

//     s32 specular_loc = glGetUniformLocation(self->programID, "theta_MaterialSpecularStrength");

//     if(specular_loc == -1) {
//         THETA_WARN("theta_shader_program_set_ambient_light_opengl has failed. The reason being, the shader you are using does not have a proper specular property! Be sure that there is a float in your vertex shader called 'theta_MaterialSpecularStrength'!\n");
//     }

//     glUseProgram(self->programID);
//     glUniform1f(specular_loc, specular_strength);
//     glUseProgram(0);
// }

// void theta_shader_program_set_specular_highlight_opengl(theta_shader_program* program, f32 specular_highlight) {
//     theta_shader_program_opengl_specifics* self = DATA_CAST(theta_shader_program_opengl_specifics, program);

//     s32 specular_loc = glGetUniformLocation(self->programID, "theta_MaterialSpecularHighlight");

//     if(specular_loc == -1) {
//         THETA_WARN("theta_shader_program_set_ambient_light_opengl has failed. The reason being, the shader you are using does not have a proper specular highlight property! Be sure that there is a float in your vertex shader called 'theta_MaterialSpecularHighlight'!\n");
//     }

//     glUseProgram(self->programID);
//     glUniform1f(specular_loc, powf(2.0f, specular_highlight));
//     glUseProgram(0);
// }