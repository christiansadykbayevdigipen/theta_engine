#include "oglshader.h"

#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <string.h>
#include <glad/glad.h>
#include <math.h>

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
    program->give_albedo = &theta_shader_program_give_albedo_opengl;
    program->set_color = &theta_shader_program_set_color_opengl;
    program->set_light = &theta_shader_program_set_light_opengl;
    program->set_ambient_light = &theta_shader_program_set_ambient_light_opengl;
    program->set_specular = &theta_shader_program_set_specular_opengl;
    program->set_specular_highlight = &theta_shader_program_set_specular_highlight_opengl;
}

void theta_shader_program_set_mvp_opengl(theta_shader_program* program, mat4 model, mat4 view, mat4 projection) {
    u32 p_id = DATA_CAST(theta_shader_program_opengl_specifics, program)->programID;

    u32 model_location = glGetUniformLocation(p_id, "model");
    u32 view_location = glGetUniformLocation(p_id, "view");
    u32 proj_location = glGetUniformLocation(p_id, "projection");

    glUseProgram(p_id);

    glUniformMatrix4fv(model_location, 1, GL_FALSE, model[0]);
    glUniformMatrix4fv(view_location, 1, GL_FALSE, view[0]);
    glUniformMatrix4fv(proj_location, 1, GL_FALSE, projection[0]);

    glUseProgram(0);
}

void theta_shader_program_destroy_opengl(theta_shader_program* program) {
    THETA_PROFILE();
    
    glDeleteProgram(DATA_CAST(theta_shader_program_opengl_specifics, program)->programID);
}

void theta_shader_program_give_albedo_opengl(theta_shader_program* program, theta_texture* albedo_texture) {
    THETA_PROFILE();
    theta_shader_program_opengl_specifics* progspec = DATA_CAST(theta_shader_program_opengl_specifics, program);

    program->albedo_texture = albedo_texture;

    glUseProgram(progspec->programID);

    DATA_CAST(theta_shader_program_opengl_specifics, program)->albedo_unit_id = 0;

    s32 loc = glGetUniformLocation(progspec->programID, "theta_Albedo");

    if(loc == -1) {
        THETA_WARN("theta_shader_program_give_albedo_opengl has failed. The reason being, the shader you are using does not have a proper albedo texture property! Be sure that there is a Uniform Sampler2D called 'theta_Albedo' in your vertex shader!\n");
        return;
    }

    glUniform1i(loc, progspec->albedo_unit_id);
    
    glUseProgram(0);
}

void theta_shader_program_set_color_opengl(theta_shader_program* program, vec3 color) {
    theta_shader_program_opengl_specifics* self = DATA_CAST(theta_shader_program_opengl_specifics, program);

    s32 location = glGetUniformLocation(self->programID, "color");

    //THETA_ASSERT(location == -1, "");
    if(location == -1) {
        THETA_WARN("theta_shader_program_set_color_opengl has failed. The reason being, the shader that you are using does not have a uniform vec4 named 'color'!\n");
        return;
    }

    glUseProgram(self->programID);

    glUniform4f(location, color[0], color[1], color[2], 1.0f);
    
    glUseProgram(0);
}

void theta_shader_program_set_light_opengl(theta_shader_program* program, theta_light_descriptor light, vec3 viewing_position) {
    theta_shader_program_opengl_specifics* self = DATA_CAST(theta_shader_program_opengl_specifics, program);

    s32 loc = glGetUniformLocation(self->programID, "theta_SceneLightPos");
    
    if(loc == -1) {
        THETA_WARN("theta_shader_program_set_light_position_opengl has failed. The reason being, the shader you are using does not have a proper light positon property! Be sure that there is a Vec3 in your shader called 'theta_SceneLightPos'!\n");
    }

    s32 color_loc = glGetUniformLocation(self->programID, "theta_SceneLightColor");
    if(color_loc == -1) {
        THETA_WARN("theta_shader_program_set_light_position_opengl has failed. The reason being, the shader you are using does not have a proper light color property! Be sure that there is a Vec3 in your shader called 'theta_SceneLightColor'!\n");
    }

    s32 viewing_loc = glGetUniformLocation(self->programID, "theta_CameraViewingLocation");
    if(viewing_loc == -1) {
        THETA_WARN("theta_shader_program_set_light_position_opengl has failed. The reason being, the shader you are using does not have a proper viewing camera property! Be sure that there is a Vec3 in your shader called 'theta_CameraViewingLocation'!\n");
    }
    
    glUseProgram(self->programID);

    glUniform3f(loc, light.transform.position[0], light.transform.position[1], light.transform.position[2]);
    glUniform3f(color_loc, light.light_color[0], light.light_color[1], light.light_color[2]);
    glUniform3f(viewing_loc, viewing_position[0], viewing_position[1], viewing_position[2]);

    glUseProgram(0);
}

void theta_shader_program_set_ambient_light_opengl(theta_shader_program* program, theta_light_ambient_descriptor light) {
    theta_shader_program_opengl_specifics* self = DATA_CAST(theta_shader_program_opengl_specifics, program);

    s32 ambient_strength_loc = glGetUniformLocation(self->programID, "theta_AmbientStrength");
    
    if(ambient_strength_loc == -1) {
        THETA_WARN("theta_shader_program_set_ambient_light_opengl has failed. The reason being, the shader you are using does not have a proper ambien light property! Be sure that there is a float in your vertex shader called 'theta_AmbientStrength'!\n");
    }

    s32 ambient_color_loc = glGetUniformLocation(self->programID, "theta_AmbientColor");
    
    if(ambient_color_loc == -1) {
        THETA_WARN("theta_shader_program_set_ambient_light_opengl has failed. The reason being, the shader you are using does not have a proper ambient light property! Be sure that there is a vec3 in your vertex shader called 'theta_AmbientColor'!\n");
    }
    
    glUseProgram(self->programID);

    glUniform1f(ambient_strength_loc, light.ambient_strength);
    glUniform3f(ambient_color_loc, light.light_color[0], light.light_color[1], light.light_color[2]);

    glUseProgram(0);
}

void theta_shader_program_set_specular_opengl(theta_shader_program* program, f32 specular_strength) {
    theta_shader_program_opengl_specifics* self = DATA_CAST(theta_shader_program_opengl_specifics, program);

    s32 specular_loc = glGetUniformLocation(self->programID, "theta_MaterialSpecularStrength");

    if(specular_loc == -1) {
        THETA_WARN("theta_shader_program_set_ambient_light_opengl has failed. The reason being, the shader you are using does not have a proper specular property! Be sure that there is a float in your vertex shader called 'theta_MaterialSpecularStrength'!\n");
    }

    glUseProgram(self->programID);
    glUniform1f(specular_loc, specular_strength);
    glUseProgram(0);
}

void theta_shader_program_set_specular_highlight_opengl(theta_shader_program* program, f32 specular_highlight) {
    theta_shader_program_opengl_specifics* self = DATA_CAST(theta_shader_program_opengl_specifics, program);

    s32 specular_loc = glGetUniformLocation(self->programID, "theta_MaterialSpecularHighlight");

    if(specular_loc == -1) {
        THETA_WARN("theta_shader_program_set_ambient_light_opengl has failed. The reason being, the shader you are using does not have a proper specular highlight property! Be sure that there is a float in your vertex shader called 'theta_MaterialSpecularHighlight'!\n");
    }

    glUseProgram(self->programID);
    glUniform1f(specular_loc, powf(2.0f, specular_highlight));
    glUseProgram(0);
}