//
// Created by Vitor Hugo on 28/12/2021.
//
#include "Population/population.h"

#ifndef TSP_GENERATION_H
#define TSP_GENERATION_H

#include <stdlib.h>

typedef struct generation {
    uint32_t id;
    POPULATION parent_population;
    POPULATION child_population;
} GENERATION;

/**
 * inserts first population into first generation
 * @param booked_trip client booked trip
 * @param size_population size of population
 * @return first population
 */
POPULATION insert_first_population(const COUNTRY *booked_trip, int size_population);

/**
 * inserts child population into generation
 * @param generation address of generation
 * @param num_elitism number of elitism
 * @param mutation_prob mutation probability
 * @return child population
 */
POPULATION insert_child_population(GENERATION *generation, int num_elitism, float mutation_prob);

/**
 * copies every value of a population
 * @param population population to copy
 * @return copied population
 */
POPULATION deep_copy_population(POPULATION *population);

#endif //TSP_GENERATION_H
