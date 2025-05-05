#include "list.h"

#include <stddef.h>
#include <memory.h>
#include <malloc.h>
#include <stdio.h>

// The amount of room the dynamic list gets to start out with. This is not in bytes, but in element count. Multiply by element_size to get the number of bytes.
static u32 g_starting_buffer_length = 20;

// Every time the dynamic list runs out of room and needs to be reallocated, it will reallocate g_reallocation_weight amount of elements. Multiply by element_size to get the number of bytes.
static u32 g_reallocation_weight = 10;

void theta_dynamic_list_init(theta_dynamic_list* list, u32 element_size) {
    list->element_size = element_size;
    list->length = 0;
    list->current_buffer_length = g_starting_buffer_length;
    list->elements = malloc(element_size * list->current_buffer_length);
}

void theta_dynamic_list_init_args(theta_dynamic_list* list, void** elements, u32 element_size, u32 length) {
    list->element_size = element_size;
    list->length = length;
    list->current_buffer_length = g_starting_buffer_length + element_size;
    list->elements = malloc(element_size * list->current_buffer_length);

    memcpy(list->elements, elements, element_size);
}

void theta_dynamic_list_push_back(theta_dynamic_list* list, void* element) {
    // Check to see if there is not enough memory for the operation
    if(list->current_buffer_length*list->element_size <= (list->length+1) * list->element_size) {
        list->current_buffer_length += g_reallocation_weight;
        list->elements = realloc(list->elements, list->current_buffer_length * list->element_size);
    }

    memcpy(list->elements + list->length, element, list->element_size);

    list->length++;
}

void* theta_dynamic_list_get(theta_dynamic_list* list, u32 index) {
    if(index >= list->length)
        return NULL;
    if(index < 0)
        return NULL;
    
    return list->elements[index];
}

void theta_dynamic_list_pop_back(theta_dynamic_list* list) {
    if(list->length < 1)
        return;
    
    list->length--;
}