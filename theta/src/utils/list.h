#pragma once

#include "core.h"

/*Linked List*/

typedef struct theta_node{
    void* data;
    struct theta_node* next;
}theta_node;

// Creates a new node of a linked list!
THETA_API theta_node* theta_node_init(void* data, u32 data_size);

// Inserts a new node before the head of the linked list.
THETA_API theta_node* theta_node_insert_at_head(theta_node* head, void* data, u32 data_size);

// Removes the head node of the linked list and returns a new head.
THETA_API theta_node* theta_node_delete_at_head(theta_node* head);

// Pushes new data at the end of the list. The return value of this function doesn't really matter but it just returns the head. Obviously the head is not modified in this function, so it's just redundent data in case you are passing this function into another function.
THETA_API theta_node* theta_node_push_back(theta_node* head, void* data, u32 data_size);

// Pops the end of the list off. Again, same thing with the return value as with theta_node_push_back.
THETA_API theta_node* theta_node_pop_back(theta_node* head);

// Gets the length of a linked list starting from the head
THETA_API u32 theta_node_get_length(theta_node* head);

// TODO: Implement
THETA_API void* theta_node_create_array(theta_node* head, u32 data_size);

THETA_API void theta_node_free_all(theta_node* head);