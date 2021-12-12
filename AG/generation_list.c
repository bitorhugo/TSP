//
// Created by Vitor Hugo on 12/12/2021.
//

#include "ag.h"

GENERATION_LIST* allocate_memory_generation_node() {
    GENERATION_LIST *new_generation_node = calloc(1, sizeof(GENERATION_LIST));
    return new_generation_node;
}

void insert_generation (GENERATION_LIST **head, bool at_head) {
    if (is_list_empty(head)) at_head = true;

    GENERATION_LIST *new_generation_node = allocate_memory_generation_node();

    if (at_head) {
        *head = new_generation_node;
        new_generation_node->num_of_generation_nodes += 1;
    }
    else {
        GENERATION_LIST *temp_node = *head;
        while (temp_node != NULL) {
            temp_node = temp_node->next_generation_node;
        }
        temp_node->next_generation_node = new_generation_node;
    }

}

