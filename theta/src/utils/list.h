#pragma once

#include "core.h"

/*
@brief This is a dynamic, auto-resizing array implementation in C. This is essentially like the vector class in C++
@param elements A pointer to a list of generic elements
@param element_size The size of each element in the list of elements
@param length The number of elements in the list
@param current_buffer_length The number of elements that can currently fit in the elements array. Once exceeded, this will increase and be reallocated.
*/
typedef struct {
    void** elements;
    u32 element_size;
    u32 length;
    u32 current_buffer_length;
}theta_dynamic_list;

/*
@brief Initializes an empty dynamic list.
@param list A pointer to an uninitialized dynamic list structure.
@param element_size The size (in bytes) of each element in this list.
*/
THETA_API void theta_dynamic_list_init(theta_dynamic_list* list, u32 element_size);

/*
@brief Initializes a dynamic list from a pre-existing array.
@param list A pointer to an uninitialized dynamic list structure.
@param elements A pointer to a list of generic elements
@param The size (in bytes) of each element in the list of elements
@param length The number of elements in the array
*/
THETA_API void theta_dynamic_list_init_args(theta_dynamic_list* list, void** elements, u32 element_size, u32 length);

/*
@brief Pushes an element to the back of the list
@param list A pointer to an initialized dynamic list structure.
@param element The element to push to the list.
*/
THETA_API void theta_dynamic_list_push_back(theta_dynamic_list* list, void* element);

/*
@brief Gets the value at an index
@param list A pointer to an initialized dynamic list structure
@param index The index of the element.
*/
THETA_API void* theta_dynamic_list_get(theta_dynamic_list* list, u32 index);

/*
@brief This pops an element off the back of the list.
@param list A pointer to an initialized dynamic list structure.
*/
THETA_API void theta_dynamic_list_pop_back(theta_dynamic_list* list);

// TODO: Add other list functionality. For now, other important parts have to get implemented.