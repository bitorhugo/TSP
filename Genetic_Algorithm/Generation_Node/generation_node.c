//
// Created by Vitor Hugo on 28/12/2021.
//

#include "generation_node.h"

void insert_best_population (GENERATION_NODE *node);


GENERATION_NODE* allocate_memory_generation_node (GENERATION generation) {
    GENERATION_NODE *new_node = calloc(1, sizeof(GENERATION_NODE));
    new_node->generation = generation;
    insert_best_population(new_node);
    return new_node;
}

void deallocate_memory_generation_node (GENERATION_NODE *node) {
    free(node);
}


void insert_best_population (GENERATION_NODE *node) {
    // set number of chromosomes
    node->best_population.num_chromosomes = 2;
    // allocate memory for chromosomes
    node->best_population.chromosomes = allocate_memory_chromosome(node->best_population.num_chromosomes);

    // set chromosomes
    for (size_t i = 0; i < node->best_population.num_chromosomes; ++i) {
        CHROMOSOME *temp_chromo_old = node->generation.parent_population.chromosomes + i;
        CHROMOSOME *tem_chromo_new = node->best_population.chromosomes + i;
        *tem_chromo_new = *temp_chromo_old;
    }
}


