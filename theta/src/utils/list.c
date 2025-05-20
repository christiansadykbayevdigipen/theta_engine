#include "list.h"

#include <stddef.h>
#include <memory.h>
#include <malloc.h>
#include <stdio.h>

// The amount of room the dynamic list gets to start out with. This is not in bytes, but in element count. Multiply by element_size to get the number of bytes.
//static u32 g_starting_buffer_length = 20;

// Every time the dynamic list runs out of room and needs to be reallocated, it will reallocate g_reallocation_weight amount of elements. Multiply by element_size to get the number of bytes.
//static u32 g_reallocation_weight = 10;

void theta_dynamic_list_init(theta_dynamic_list* list, u32 element_size) {
    list->element_size = element_size;
    list->length = 0;
    list->current_buffer_length = 1;
    list->elements = malloc(element_size * list->current_buffer_length);
}

void theta_dynamic_list_init_args(theta_dynamic_list* list, void** elements, u32 element_size, u32 length) {
    list->element_size = element_size;
    list->length = length;
    list->current_buffer_length = element_size;
    list->elements = malloc(element_size * list->current_buffer_length);

    memcpy(list->elements, elements, element_size);
}

void theta_dynamic_list_push_back(theta_dynamic_list* list, void* element) {
    // Check to see if there is not enough memory for the operation
    if(list->current_buffer_length*list->element_size <= (list->length+1) * list->element_size) {
        list->current_buffer_length *= 2;
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

void theta_dynamic_list_pop_front(theta_dynamic_list* list) {
    
}


/*Linked List*/

theta_node* theta_node_init(void* data, u32 data_size) {
    theta_node* new_node = INIT_STRUCT(theta_node);

    new_node->data = malloc(data_size);
    new_node->next = NULL;

    memcpy(new_node->data, data, data_size);

    return new_node;
}

theta_node* theta_node_insert_at_head(theta_node* head, void* data, u32 data_size) {
    theta_node* new_node = INIT_STRUCT(theta_node);

    new_node->data = malloc(data_size);
    new_node->next = head;

    memcpy(new_node->data, data, data_size);

    return new_node;
}

theta_node* theta_node_delete_at_head(theta_node* head) {
    if(head == NULL) return NULL;

    free(head->data);

    theta_node* next_in_succession = head->next;

    free(head);

    head = next_in_succession;

    return head;
}

theta_node* theta_node_push_back(theta_node* head, void* data, u32 data_size) {
    theta_node* temp_node = head;

    // Gets the last node in the list.
    while(temp_node->next != NULL) {
        temp_node = temp_node->next;
    }

    temp_node->next = INIT_STRUCT(theta_node);
    theta_node* succession = temp_node->next;

    succession->data = malloc(data_size);
    succession->next = NULL;
    memcpy(succession->data, data, data_size);

    return head;
}

theta_node* theta_node_pop_back(theta_node* head) {
    theta_node* temp_node = head;

    if(head->next == NULL) {
        free(head->data);
        free(head);
        return NULL;
    }

    // Gets the second to last node in the list.
    while(TRUE) {
        if(temp_node == NULL) break;
        if(temp_node->next == NULL) break;
        if(temp_node->next->next == NULL) break;

        temp_node = temp_node->next;
    }

    free(temp_node->next->data);

    free(temp_node->next);
    
    temp_node->next = NULL;

    return head;
}

void theta_node_free_all(theta_node* head) {
    theta_node* temp_node = head;

    // Gets the second to last node in the list.
    while(TRUE) {
        if(temp_node == NULL) break;
        if(temp_node->next == NULL) break;
        if(temp_node->next->next == NULL) break;

        temp_node = temp_node->next;
    }

    if(temp_node->next == NULL) {
        // This is the last node.
        // Just free this one and be done with everything
        free(temp_node->data);
        free(temp_node);
        return;
    }

    free(temp_node->next->data);
    free(temp_node->next);
    temp_node->next = NULL;
    
    theta_node_free_all(head);
}