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

void insert_generation (GENERATION_LL *list, bool at_head, GENERATION generation);
GENERATION* search_generation (GENERATION_LL *list, uint32_t id);

void deallocate_generation_linked_list (GENERATION_LL *list);

#endif //TSP_GENERATION_LINKED_LIST_H
