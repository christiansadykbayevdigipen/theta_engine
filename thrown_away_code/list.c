#include "list.h"

#include <stddef.h>
#include <memory.h>
#include <malloc.h>
#include <stdio.h>

u32 theta_linked_list_get_length(theta_node* front) {
    u32 length = 0;
    
    while(front != NULL) {
        front = front->next;
        length++;
    }

    return length;
}

theta_node* theta_linked_list_insert_at_front(theta_node* front, void* element, u32 element_size) {
    theta_node* new_node = (theta_node*)(malloc(sizeof(theta_node)));

    new_node->data = malloc(element_size);
    new_node->next = front;
    
    //memcpy_s(new_node->data, element_size, element, element_size);
    memcpy(new_node->data, element, element_size);

    return new_node;
}

theta_node* theta_linked_list_insert(theta_node* front, void* element, u32 element_size, theta_node* given_node) {
    theta_node* curr = front;

    // Look for the given node.
    while(curr != given_node) {
        curr = curr->next;
    }

    // If the given node is not found, return early.
    if(curr != given_node) return front;

    // Initialize the new node
    theta_node* new_node = (theta_node*)malloc(sizeof(theta_node));
    new_node->data = malloc(element_size);
    memcpy(new_node->data, element, element_size);

    // Insert the node after the given node
    new_node->next = given_node->next;
    given_node->next = new_node;

    return front;
}

theta_node* theta_linked_list_insert_pos(theta_node* front, void* element, u32 element_size, u32 given_position) {
    theta_node* curr = front;
    
    // Traverse the linked list until position - 1
    for(u32 i = 0; i < given_position - 1; i++) {
        curr = curr->next;
    }

    // Initialize the new node
    theta_node *new_node = (theta_node *)malloc(sizeof(theta_node));
    new_node->data = malloc(element_size);
    memcpy(new_node->data, element, element_size);

    // Change the next pointers of the surrounding nodes.
    new_node->next = curr->next;
    curr->next = new_node;

    return front;
}

theta_node* theta_linked_list_push(theta_node* front, void* element, u32 element_size) {
    theta_node* curr = front;

    if(curr == NULL) {
        curr = (theta_node*)malloc(sizeof(theta_node));
        curr->data = malloc(element_size);
        memcpy(curr->data, element, element_size);
        curr->next = NULL;
        return curr;
    }

    // Get the last element
    while(curr->next != NULL) {
        curr = curr->next;
    }

    curr->next = (theta_node*)malloc(sizeof(theta_node*));
    curr->next->data = malloc(element_size);
    curr->next->next = NULL;
    memcpy(curr->next->data, element, element_size);
}

theta_node* theta_linked_list_delete_at_front(theta_node* front) {
    if(front == NULL) return;

    theta_node* new_front = front->next;
    free(front->data);
    free(front);

    return new_front;
}

void theta_linked_list_pop(theta_node* front) {
    if(front == NULL) return;

}