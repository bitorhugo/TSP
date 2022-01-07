//
// Created by Vitor Hugo on 28/12/2021.
//
#include "Generation/generation.h"


#ifndef TSP_GENERATION_NODE_H
#define TSP_GENERATION_NODE_H

typedef struct generation_node {
    GENERATION generation;
    POPULATION best_population;
    struct generation_node *next_node;
}GENERATION_NODE;

/**
 * allocates memory for a generation node
 * @param generation generation to insert
 * @return address of generation node
 */
GENERATION_NODE* allocate_memory_generation_node (GENERATION generation);
/**
 * frees generation node
 * @param node address of generation node
 */
void deallocate_memory_generation_node (GENERATION_NODE *node);



#endif //TSP_GENERATION_NODE_H
