#include "input.h"

#include <memory.h>
#include <malloc.h>
#include <string.h>

#include "stb_ds.h"

/*
Well, there is a bug that when you press the negative key and then release the other key (so changing directions really quickly), it halts the input sort of. 
So, when the positive key is being pressed and then the negative key gets pressed, it it should just cancel the positive key and not do any event for the releasing of that key. 

BUG -- FIXED
BUG -- ITS BACK AGAIN?
BUG -- ITS FIXED AGAIN
*/

theta_input_system* theta_input_system_init() {
    THETA_PROFILE();

    theta_input_system* input = INIT_STRUCT(theta_input_system);

    input->inputs = NULL;

    return input;
}

void theta_input_system_bind_input(theta_input_system* system, const char* tag, theta_input_layout layout, void (*input_callback)(vec3)) {
    THETA_PROFILE();
    theta_input_descriptor descriptor;
    descriptor.input_callback = input_callback;
    descriptor.layout[0] = layout;
    descriptor.layout_count = 1;
    strcpy(descriptor.tag, tag);


    arrpush(system->inputs, descriptor);
}

void theta_input_system_on_key_down(theta_input_system* system, char key) {
    for(u32 i = 0; i < arrlen(system->inputs); i++) { // Go through each input binding
        theta_input_descriptor* descriptor = &system->inputs[i];
        
        for(u32 k = 0; k < descriptor->layout_count; k++) { // Loops until it finds the keyboard layout (if there is one). And then, calls the correct callbacks.
            if(descriptor->layout[k].type == THETA_INPUT_LAYOUT_TYPE_KEYBOARD) {
                theta_input_layout_keyboard* kb = (theta_input_layout_keyboard*)(descriptor->layout[k].input_layout);

                if(kb->positive == key) {
                    vec3 ret = {1.0f, 0.0f, 0.0f};
                    descriptor->input_callback(ret);
                    descriptor->status = 1;
                }
                if(kb->negative == key) {
                    vec3 ret = {-1.0f, 0.0f, 0.0f};
                    descriptor->input_callback(ret);
                    descriptor->status = -1;
                }
            }
        }
    }
}

void theta_input_system_on_key_up(theta_input_system* system, char key) {
        for(u32 i = 0; i < arrlen(system->inputs); i++) { // Go through each input binding
        theta_input_descriptor* descriptor = &system->inputs[i];
        
        for(u32 k = 0; k < descriptor->layout_count; k++) { // Loops until it finds the keyboard layout (if there is one). And then, calls the correct callbacks.
            if(descriptor->layout[k].type == THETA_INPUT_LAYOUT_TYPE_KEYBOARD) {
                theta_input_layout_keyboard* kb = (theta_input_layout_keyboard*)(descriptor->layout[k].input_layout);
                
                /*Basically, if it's heading the negative direction anyways, it should not call the callback to set the axis back to zero. This would make it so that when you are changing directions very quickly, it just halts your movement until you repress the key*/
                if(kb->positive == key && descriptor->status == -1) continue;
                if(kb->negative == key && descriptor->status == 1) continue;
                
                
                if(kb->positive == key || kb->negative == key) {
                    vec3 ret = {0.0f, 0.0f, 0.0f};
                    descriptor->input_callback(ret);
                }
            }
        }
    }
}

void theta_input_system_on_cursor(theta_input_system* system, f64 x_position, f64 y_position) {
    for(u32 i = 0; i < arrlen(system->inputs); i++) { // Go through each input binding
        theta_input_descriptor* descriptor = &system->inputs[i];
        for(u32 k = 0; k < descriptor->layout_count; k++) {
            if(descriptor->layout[k].type == THETA_INPUT_LAYOUT_TYPE_CURSOR) {
                vec3 ret = {x_position, y_position, 0.0f};
                descriptor->input_callback(ret);
            }
        }
    }
}

void theta_input_system_destroy(theta_input_system* system) {
    THETA_PROFILE();
    free(system);
}