//
// Created by Vitor Hugo on 28/12/2021.
//

#include "population.h"

/*
 * private prototypes
 */
void swap_cromo(CHROMOSOME *a, CHROMOSOME *b);

/*
 * public implementation
 */

void deallocate_memory_population (POPULATION *population) {
    if (population->num_chromosomes > 1) {
        for (int i = population->num_chromosomes - 1; i >= 0; --i) {
            CHROMOSOME *temp_chromo = population->chromosomes + i;
            deallocate_memory_chromosome(temp_chromo);
        }
        // frees chromosomes array
        free(population->chromosomes);
    }
}

void sort_chromosomes_by_fitness(POPULATION *population) {

    // Selection Sort used due to low amount of values to compare
    for (int i = 0; i < population->num_chromosomes - 1; ++i) {
        for (int j = i + 1; j < population->num_chromosomes; ++j) {
            CHROMOSOME *a = population->chromosomes + i;
            CHROMOSOME *b = population->chromosomes + j;

            // if chromosome b fitness value is bigger, swap
            if (b->fitness_value > a->fitness_value) {
                swap_cromo(a, b);
            }
        }
    }

}

void insert_chromosomes(POPULATION *population, const COUNTRY *booked_trip) {

    // allocate space for 'x' chromosomes
    population->chromosomes = allocate_memory_chromosome(population->num_chromosomes);

    // insert genes into each chromosome of population
    for (size_t i = 0; i < population->num_chromosomes; ++i) {
        CHROMOSOME *temp_chromo = population->chromosomes + i;

        // set number of genes to insert
        temp_chromo->num_genes = booked_trip->num_of_cities;

        // insert genes into chromosome
        insert_gene(temp_chromo, booked_trip);

        // shuffle genes to create random routes
        shuffle_genes(temp_chromo);

        // calculate fitness value of chromosome
        temp_chromo->fitness_value = calculate_fitness(temp_chromo);
    }

}

/*
 * private implementation
 */
void swap_cromo(CHROMOSOME *a, CHROMOSOME *b) {
    CHROMOSOME temp = *a;
    *a = *b;
    *b = temp;
}