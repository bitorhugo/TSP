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
    POPULATION fittest_chromosome;
}GENERATION;

POPULATION insert_first_population (GENERATION *generation, const COUNTRY *booked_trip, int size_population);
POPULATION insert_child_population (GENERATION *generation, int num_elitism, float mutation_prob);

#endif //TSP_GENERATION_H
