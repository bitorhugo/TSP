//
// Created by Vitor Hugo on 28/12/2021.
//

#include "generation_linked_list.h"
#include <stdio.h>


void insert_generation (GENERATION_LL *list, bool at_head, GENERATION generation) {
    if (list->list_size < 1) {
        list->head = allocate_memory_generation_node(generation);
        list->list_size = 1;
    }
    else {
        GENERATION_NODE *new_node = allocate_memory_generation_node(generation);
        if (at_head) {
            new_node->next_node = list->head;
            list->head = new_node;
            list->list_size += 1;
        }
        else {
            GENERATION_NODE *temp_node = list->head;
            while (temp_node->next_node != NULL) {
                temp_node = temp_node->next_node;
            }
            temp_node->next_node = new_node;
            list->list_size += 1;
        }
    }
}

GENERATION* search_generation (GENERATION_LL *list, uint32_t id) {
    if (list->list_size < 1) {
        fprintf(stderr, "ERROR: NO GENERATIONS FOUND\n");
        return NULL;
    }

    GENERATION_NODE *temp_node = list->head;
    while (temp_node != NULL) {
        if (temp_node->generation.id == id) {
            return &temp_node->generation;
        }
        temp_node = temp_node->next_node;
    }

    fprintf(stderr, "ERROR: GENERATION NOT FOUND\n");
    return NULL;
}

void deallocate_generation_linked_list (GENERATION_LL *list) {
    free(list);
}