//
// Created by Vitor Hugo on 28/12/2021.
//

#include "generation_node.h"

/*
 * private prototype
 */
/**
 * save population with best two chromosomes into generation node
 * @param node generation node
 */
void insert_best_population(GENERATION_NODE *node);

/*
 * public implementations
 */
GENERATION_NODE *allocate_memory_generation_node(GENERATION generation) {
    GENERATION_NODE *new_node = calloc(1, sizeof(GENERATION_NODE));
    new_node->generation = generation;
    insert_best_population(new_node);
    return new_node;
}

void deallocate_memory_generation_node(GENERATION_NODE *node) {
    free(node);
}

/*
 * private implementation
 */
void insert_best_population(GENERATION_NODE *node) {
    // set number of chromosomes
    node->best_population.num_chromosomes = 2;
    // allocate memory for chromosomes
    node->best_population.chromosomes = allocate_memory_chromosome(node->best_population.num_chromosomes);

    // set chromosomes
    for (size_t i = 0; i < node->best_population.num_chromosomes; ++i) {
        CHROMOSOME *temp_chromo_old = node->generation.parent_population.chromosomes + i;
        CHROMOSOME *temp_chromo_new = node->best_population.chromosomes + i;

        temp_chromo_new->genes = allocate_memory_gene(temp_chromo_old->num_genes);

        for (size_t j = 0; j < temp_chromo_old->num_genes; ++j) {
            GENE *temp_gene_old = temp_chromo_old->genes + j;
            GENE *temp_gene_new = temp_chromo_new->genes + j;

            temp_gene_new->id = temp_gene_old->id;
            temp_gene_new->x = temp_gene_old->x;
            temp_gene_new->y = temp_gene_old->y;

        }
    }
}


