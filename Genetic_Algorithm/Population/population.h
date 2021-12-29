//
// Created by Vitor Hugo on 28/12/2021.
//
#include "Chromosome/chromosome.h"

#ifndef TSP_POPULATION_H
#define TSP_POPULATION_H

typedef struct population {
    CHROMOSOME *chromosomes;
    int num_chromosomes;
}POPULATION;

POPULATION* allocate_memory_population ();
void insert_chromosomes (POPULATION *population, const COUNTRY *booked_trip);
void sort_chromosomes_by_fitness (POPULATION *population);

#endif //TSP_POPULATION_H
