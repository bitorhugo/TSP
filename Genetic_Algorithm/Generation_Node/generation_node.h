//
// Created by Vitor Hugo on 28/12/2021.
//
#include "Generation/generation.h"


#ifndef TSP_GENERATION_NODE_H
#define TSP_GENERATION_NODE_H

typedef struct generation_node {
    GENERATION generation;
    struct generation_node *next_node;
}GENERATION_NODE;

GENERATION_NODE* allocate_memory_generation_node (GENERATION generation);

void deallocate_memory_generation_node (GENERATION_NODE *node);


#endif //TSP_GENERATION_NODE_H
