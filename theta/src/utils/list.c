#include "list.h"

#include <stddef.h>
#include <memory.h>
#include <malloc.h>
#include <stdio.h>


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

u32 theta_node_get_length(theta_node* head) {
    u32 i = 0;

    theta_node* temp_node = head;

    while(temp_node != NULL) {
        temp_node = temp_node->next;
        i++;
    }

    return i;
}

void* theta_node_create_array(theta_node* head, u32 data_size) {
    
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