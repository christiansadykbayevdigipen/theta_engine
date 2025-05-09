#include "oglshader.h"

#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <string.h>
#include <glad/gl.h>

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

static u32 compile_shader(u32 type, char* src) {
    u32 shaderID = glCreateShader(type);

    glShaderSource(shaderID, 1, &src, NULL);

    glCompileShader(shaderID);

    s32 compile_status = NULL;

    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compile_status);

    if(!compile_status) {
        char message[1024];
        s32 log_length;

        glGetShaderInfoLog(shaderID, 1024, &log_length, message);

        THETA_FATAL("compile_shader has failed. The reason being, OpenGL returned this error: %s\n", message);
        return;
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

    s32 status = NULL;

    glGetProgramiv(program, GL_LINK_STATUS, &status);

    if(!status) {
        char message[1024];
        s32 log_length;

        glGetProgramInfoLog(program, 1024, &log_length, message);

        THETA_FATAL("create_and_link_program has failed. The reason being, OpenGL returned this error: %s\n", message);
        return;
    }

    return program;
}

void theta_shader_program_init_opengl(theta_shader_program* program, const char* filename) {
    THETA_PROFILE();
    
    program->uninterpreted_data = malloc(sizeof(theta_shader_program_opengl_specifics));
    
    u32 current_buffer_size = 1000;
    char* full_source = malloc(sizeof(char) * current_buffer_size);
    
    FILE* file = NULL;
    
    
    
    THETA_ASSERT(0 == fopen_s(&file, filename, "r"), "theta_shader_program_init_opengl has failed. The reason being, the shader program file that has been requested does not currently exist.");
    
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
    program->give_albedo = &theta_shader_program_give_albedo_opengl;
}

void theta_shader_program_set_mvp_opengl(theta_shader_program* program, theta_mat4x4f model, theta_mat4x4f view, theta_mat4x4f projection) {
    u32 p_id = DATA_CAST(theta_shader_program_opengl_specifics, program)->programID;

    u32 model_location = glGetUniformLocation(p_id, "model");
    u32 view_location = glGetUniformLocation(p_id, "view");
    u32 proj_location = glGetUniformLocation(p_id, "projection");

    float newmodel[16];
    for(int y = 0; y < 4; y++) {
        for(int x = 0; x < 4; x++) {
            int index1d = (y * 4) + x;
            newmodel[index1d] = model.matrix[y][x];
        }
    }

    float newview[16];
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            int index1d = (y * 4) + x;
            newview[index1d] = view.matrix[y][x];
        }
    }

    float newproj[16];
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            int index1d = (y * 4) + x;
            newproj[index1d] = projection.matrix[y][x];
        }
    }

    glUseProgram(p_id);

    glUniformMatrix4fv(model_location, 1, GL_FALSE, newmodel);
    glUniformMatrix4fv(view_location, 1, GL_FALSE, newview);
    glUniformMatrix4fv(proj_location, 1, GL_FALSE, newproj);

    glUseProgram(0);
}

void theta_shader_program_destroy_opengl(theta_shader_program* program) {
    glDeleteProgram(DATA_CAST(theta_shader_program_opengl_specifics, program)->programID);
}

void theta_shader_program_give_albedo_opengl(theta_shader_program* program, const char* filepath) {
    THETA_PROFILE();
    program->tex = INIT_STRUCT(theta_texture);

    theta_texture_init(program->tex, filepath);

    theta_shader_program_opengl_specifics* progspec = DATA_CAST(theta_shader_program_opengl_specifics, program);

    glUseProgram(progspec->programID);

    DATA_CAST(theta_shader_program_opengl_specifics, program)->albedo_unit_id = 0;

    s32 loc = glGetUniformLocation(progspec->programID, "theta_Albedo");

    glUniform1i(loc, progspec->albedo_unit_id);
    
    glUseProgram(0);
}