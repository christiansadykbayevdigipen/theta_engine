#include "shader_library.h"

#include "stb_ds.h"

typedef struct {
    char identifier[MAX_STRING];
    theta_shader_program program;
}theta_shader_library_entry;

typedef struct {
    theta_shader_library_entry* entries;
}theta_shader_library;

static theta_shader_library g_library;

void theta_shader_library_init() {
    g_library.entries = NULL;
}

void theta_shader_library_add(theta_shader_program program, const char* identifier) {
    theta_shader_library_entry entry = {0};
    strcpy(entry.identifier, identifier);
    entry.program = program;

    arrpush(g_library.entries, entry);
}

theta_shader_program theta_shader_library_copy(const char* identifier) {
    // Look for the shader program associated with "identifier"
    for(u32 i = 0; i < arrlen(g_library.entries); i++) {
        theta_shader_library_entry* entry = g_library.entries + i;

        // If the identifiers are the same, we have found it
        if(strcmp(entry->identifier, identifier) == 0) {
            theta_shader_program p = entry->program;

            return p;
        }
    }

    THETA_ERROR("theta_shader_library_copy has failed. The reason being, the shader library could not find a shader associated with %s! Make sure you add that shader using theta_shader_library_add!\n", identifier);
}

void theta_shader_library_destroy() {
    arrfree(g_library.entries);
}