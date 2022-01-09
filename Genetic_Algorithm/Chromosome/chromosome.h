//
// Created by Vitor Hugo on 28/12/2021.
//

#include "Client_Linked_List/client_linked_list.h"
#include "Gene/gene.h"

#ifndef TSP_CHROMOSOME_H
#define TSP_CHROMOSOME_H

typedef struct chromosome {
    GENE *genes;
    int num_genes;
    float fitness_value;
} CHROMOSOME;

/**
 * allocates memory for a chromosome array
 * @param size size of chromosome array
 * @return address of chromosome array
 */
CHROMOSOME *allocate_memory_chromosome(int size);

/**
 * inserts a gene into chromosome
 * @param chromosome address of chromosome
 * @param booked_trip client booked trip
 */
void insert_gene(CHROMOSOME *chromosome, const COUNTRY *booked_trip);

/**
 * shuffles genes from a chromosome
 * @param chromosome address of chromosome
 */
void shuffle_genes(CHROMOSOME *chromosome);

/**
 * calculates the fitness value of a chromosome
 * @param chromosome address of chromosome
 * @return fitness value
 */
float calculate_fitness(CHROMOSOME *chromosome);

#endif //TSP_CHROMOSOME_H
