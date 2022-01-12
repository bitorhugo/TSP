//
// Created by Vitor Hugo on 28/12/2021.
//

#include "chromosome.h"
#include <math.h>
#include <time.h>

/*
 * Private prototype
 */
float euclidean_dist(GENE *first, GENE *second);

/*
 * Public implementation
 */
CHROMOSOME *allocate_memory_chromosome(int size) {
    CHROMOSOME *new_chromo = calloc(size, sizeof(CHROMOSOME));
    return new_chromo;
}

void deallocate_memory_chromosome(CHROMOSOME *chromosome) {
    // free genes array in chromosome
    deallocate_memory_gene(chromosome->genes);

}

void insert_gene(CHROMOSOME *chromosome, const COUNTRY *booked_trip) {

    // allocate memory for genes
    chromosome->genes = allocate_memory_gene(chromosome->num_genes);

    // insert values for each gene
    for (size_t i = 0; i < chromosome->num_genes; ++i) {
        GENE *temp_gene = chromosome->genes + i;
        CITY *temp_city = booked_trip->cities + i;

        // set values for each gene
        temp_gene->id = i;
        temp_gene->x = temp_city->coordinates.x;
        temp_gene->y = temp_city->coordinates.y;
    }

}

void shuffle_genes(CHROMOSOME *chromosome) {

    if (chromosome->num_genes > 1) { // has to have more than one gene for swap to occur
        srand(time(NULL));
        for (size_t i = chromosome->num_genes - 1; i > 0; --i) {
            int j = rand () % (i + 1);
            swap_gene(chromosome->genes + i, chromosome->genes + j);
        }
    }

}

float calculate_fitness(CHROMOSOME *chromosome) {

    float sum = 0;
    GENE *temp_gene;
    for (size_t i = 0; i < chromosome->num_genes; ++i) {
        temp_gene = chromosome->genes + i;
        GENE *a = temp_gene;
        GENE *b = temp_gene + 1;
        if (i == chromosome->num_genes - 1) // a = c0, b = c1, ..., a = c5, b = c0
            b = chromosome->genes;
        sum += euclidean_dist(a, b);
    }
    return ((float) 1 / sum);

}

/*
 * Private implementation
 */
float euclidean_dist(GENE *first, GENE *second) {
    return sqrtf(powf(second->x - first->x, 2) + powf(second->y - first->y, 2));
}