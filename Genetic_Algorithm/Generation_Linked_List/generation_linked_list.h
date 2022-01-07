//
// Created by Vitor Hugo on 28/12/2021.
//
#include "Generation_Node/generation_node.h"
#include <stdbool.h>
#ifndef TSP_GENERATION_LINKED_LIST_H
#define TSP_GENERATION_LINKED_LIST_H

typedef struct generation_linked_list {
    GENERATION_NODE *head;
    int list_size;
}GENERATION_LL;

/**
 * inserts a new generation into linked list
 * @param list address of linked list
 * @param at_head choose if generation is inserted at head
 * @param generation generation to insert
 */
void insert_generation (GENERATION_LL *list, bool at_head, GENERATION generation);
/**
 * searches for a generation from linked list
 * @param list address of linked list
 * @param id generation id
 * @return address of generation
 */
GENERATION* search_generation (GENERATION_LL *list, uint32_t id);
/**
 * frees generation list
 * @param list address of linked list
 */
void deallocate_generation_linked_list (GENERATION_LL *list);

#endif //TSP_GENERATION_LINKED_LIST_H
