#include "input.h"

#include <memory.h>
#include <malloc.h>
#include <string.h>

#include "stb_ds.h"

#include <cglm/cglm.h>

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
    vec2 empty = {0.0f, 0.0f};
    glm_vec2_copy(empty, input->previous_cursor_position);

    return input;
}

void theta_input_system_bind_input(theta_input_system* system, const char* tag, theta_input_layout layout, void (*input_callback)(vec3)) {
    THETA_PROFILE();

    BOOL found_input = FALSE;
    u32 input_index = 0;
    // Find the particular action that we are binding another input to
    for(u32 i = 0; i < arrlen(system->inputs); i++) {
        // We have then found the input tag.
        if(strcmp(system->inputs[i].tag, tag) == 0) {
            found_input = TRUE;
            input_index = i;
        }
    }

    if(found_input) {
        theta_input_descriptor* descriptor = &system->inputs[input_index];
        
        if(descriptor->layout_count >= MAX_LAYOUTS) {
            THETA_ERROR("theta_input_system_bind_input has failed. The reason being, the max number of layouts for a particular input type has been reached and you cannot add another input layout.\n");
            return;
        }

        descriptor->layout[descriptor->layout_count] = layout;
        descriptor->layout_count++;
    }
    else {
        theta_input_descriptor descriptor;
        descriptor.input_callback = input_callback;
        descriptor.layout[0] = layout;
        descriptor.layout_count = 1;
        strcpy(descriptor.tag, tag);
        arrpush(system->inputs, descriptor);
    }
}

void theta_input_system_on_key_down(theta_input_system* system, theta_key_code key) {
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

void theta_input_system_on_key_up(theta_input_system* system, theta_key_code key) {
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
                descriptor->status = 1;

                // Find the delta mouse cursor position
                vec2 temp = {x_position, y_position};
                vec2 result;
                glm_vec2_sub(temp, system->previous_cursor_position, result);
                
                // Then put the new cursor position as the "previous" cursor position for future calculations.
                glm_vec2_copy(temp, system->previous_cursor_position);

                // Send this to the input callback
                vec3 ret = {result[0], result[1], 0.0f};
                descriptor->input_callback(ret);
            }
        }
    }
}

void theta_input_system_after_update(theta_input_system* system) {
    for(u32 i = 0; i < arrlen(system->inputs); i++) { // Go through each input binding
        theta_input_descriptor* descriptor = &system->inputs[i];
        for(u32 k = 0; k < descriptor->layout_count; k++) {
            if(descriptor->layout[k].type == THETA_INPUT_LAYOUT_TYPE_CURSOR) {
                if(descriptor->status == 1) {
                    // Send this to the input callback
                    vec3 ret = {0.0f, 0.0f, 0.0f};
                    descriptor->input_callback(ret);
                    descriptor->status = 0;
                }
            }
        }
    }
}

void theta_input_system_destroy(theta_input_system* system) {
    THETA_PROFILE();
    free(system);
}