//
// Created by Vitor Hugo on 28/12/2021.
//

#include "generation_node.h"


GENERATION_NODE* allocate_memory_generation_node (GENERATION generation) {
    GENERATION_NODE *new_node = calloc(1, sizeof(GENERATION_NODE));
    new_node->generation = generation;
    return new_node;
}

void deallocate_memory_generation_node (GENERATION_NODE *node) {
    free(node);
}