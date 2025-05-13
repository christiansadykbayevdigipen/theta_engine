#include "input.h"

#include <memory.h>
#include <malloc.h>
#include <string.h>

theta_input_system* theta_input_system_init() {
    THETA_PROFILE();

    theta_input_system* input = INIT_STRUCT(theta_input_system);

    theta_dynamic_list_init(&input->inputs, sizeof(theta_input_descriptor));


    return input;
}

void theta_input_system_bind_input(theta_input_system* system, const char* tag, theta_input_layout layout, void (*input_callback)(theta_vector3f)) {
    THETA_PROFILE();
    theta_input_descriptor* descriptor = INIT_STRUCT(theta_input_descriptor);
    descriptor->input_callback = input_callback;
    descriptor->layout[0] = layout;
    descriptor->layout_count = 1;
    strcpy(descriptor->tag, tag);


    theta_dynamic_list_push_back(&system->inputs, &descriptor);
}

void theta_input_system_on_key_down(theta_input_system* system, char key) {
    for(u32 i = 0; i < system->inputs.length; i++) { // Go through each input binding
        theta_input_descriptor* descriptor = (theta_input_descriptor*)system->inputs.elements[i];
        
        for(u32 i = 0; i < descriptor->layout_count; i++) { // Loops until it finds the keyboard layout (if there is one). And then, calls the correct callbacks.
            if(descriptor->layout[i].type == THETA_INPUT_LAYOUT_TYPE_KEYBOARD) {
                theta_input_layout_keyboard* kb = (theta_input_layout_keyboard*)(descriptor->layout[i].input_layout);
                if(kb->positive == key) {
                    descriptor->input_callback(theta_vector3f_create_args(1.0f, 0.0f, 0.0f));
                }
                if(kb->negative == key) {
                    descriptor->input_callback(theta_vector3f_create_args(-1.0f, 0.0f, 0.0f));
                }
            }
        }
    }
}

void theta_input_system_on_key_up(theta_input_system* system, char key) {
        for(u32 i = 0; i < system->inputs.length; i++) { // Go through each input binding
        theta_input_descriptor* descriptor = (theta_input_descriptor*)system->inputs.elements[i];
        
        for(u32 i = 0; i < descriptor->layout_count; i++) { // Loops until it finds the keyboard layout (if there is one). And then, calls the correct callbacks.
            if(descriptor->layout[i].type == THETA_INPUT_LAYOUT_TYPE_KEYBOARD) {
                theta_input_layout_keyboard* kb = (theta_input_layout_keyboard*)(descriptor->layout[i].input_layout);
                if(kb->positive == key || kb->negative == key) {
                    descriptor->input_callback(theta_vector3f_create_args(0.0f, 0.0f, 0.0f));
                }
            }
        }
    }
}

void theta_input_system_destroy(theta_input_system* system) {
    THETA_PROFILE();
    free(system);
}