#pragma once

#include "core.h"

typedef struct theta_node {
    void* data;
    struct theta_node* next;
}theta_node;

/*
@brief This gets the length of a theta linked list.
@returns An unsigned integer denoting the length of the linked list.
*/
THETA_API u32 theta_linked_list_get_length(theta_node* front);

#pragma region Creation of Nodes

/*
@brief This inserts a new node directly at the front of the linked list.
@param front This is a pointer to the very first element in the linked list
@param element This is the data to insert at the front. If it is a non-pointer type already, it must then be a reference. 
@param element_size The size of the element
@returns The new front node of the linked list
*/
THETA_API theta_node* theta_linked_list_insert_at_front(theta_node* front, void* element, u32 element_size);

/*
@brief This initializes a node after a given node.
@param front This is a pointer to the very first element in the linked list
@param element This is the data to insert after the given node. If it is a non-pointer type already, it must then be a reference. 
@param element_size The size of the element
@param given_node The given node that the element should be inserted after.
@returns The new front node of the linked list
*/
THETA_API theta_node* theta_linked_list_insert(theta_node* front, void* element, u32 element_size, theta_node* given_node);

/*
@brief This initializes a node after a given position.
@param front This is a pointer to the very first element in the linked list
@param element This is the data to insert after the given position. If it is a non-pointer type already, it must then be a reference. 
@param element_size The size of the element
@param given_position The given position that the element should be inserted after.
@returns The new front node of the linked list
*/
THETA_API theta_node* theta_linked_list_insert_pos(theta_node* front, void* element, u32 element_size, u32 given_position);

/*
@brief This pushes a new node to the back of the linked list. If the length of the linked list is already 0, it just creates the first element. 
@param front This is a pointer to the very first element in the linked list
@param element This is the data to push to the back. If it is a non-pointer type already, it must then be a reference. 
@param element_size The size of the element
@returns The new front node of the linked list
*/
THETA_API theta_node* theta_linked_list_push(theta_node* front, void* element, u32 element_size);

#pragma endregion

#pragma region Deletion of Nodes

/*
@brief This deletes a linked list's front node.
@param front A pointer to the front node of linked list.
@returns The new front of the linked list.
*/
THETA_API theta_node* theta_linked_list_delete_at_front(theta_node* front);

/*
@brief This pops the last element of the linked list
@param front A pointer to the front node of the linked list.
*/
THETA_API void theta_linked_list_pop(theta_node* front);

#pragma endregion