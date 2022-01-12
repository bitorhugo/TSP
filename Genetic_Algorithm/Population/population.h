//
// Created by Vitor Hugo on 28/12/2021.
//
#include "Chromosome/chromosome.h"

#ifndef TSP_POPULATION_H
#define TSP_POPULATION_H

typedef struct population {
    CHROMOSOME *chromosomes;
    int num_chromosomes;
} POPULATION;

/**
 * allocates memory for population
 * @return address of population
 */
POPULATION *allocate_memory_population();

void deallocate_memory_population (POPULATION *population);
/**
 * inserts chromosomes into population
 * @param population address of population
 * @param booked_trip client booked trip
 */
void insert_chromosomes(POPULATION *population, const COUNTRY *booked_trip);

/**
 * sort chromosomes by their fitness value
 * @param population
 */
void sort_chromosomes_by_fitness(POPULATION *population);

#endif //TSP_POPULATION_H
