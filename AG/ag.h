//
// Created by Vitor Hugo on 28/11/2021.
//
#include "client.h"


#ifndef TSP_AG_H
#define TSP_AG_H

typedef struct gene {
    int id;
    float x;
    float y;
}GENE;

typedef struct cromossoma {
    GENE *genes;
    int num_of_genes;
    float fitness_value;
}CROMOSSOMA;

typedef struct population {
    CROMOSSOMA *cromossomas;
    int num_of_cromossomas;
}POPULATION;

typedef struct generation {
    POPULATION *population;
}GENERATION;

typedef struct generation_list {
    GENERATION generation;
    int num_of_generations;
    struct generation_list *next_generation;
}GENERATION_LIST;

//------------------POPULATION-------------------------//

POPULATION* create_initial_population (COUNTRY *country_to_visit, int size_of_population);

void insert_population(POPULATION *population, COUNTRY *temp_country, int size_of_population);

POPULATION* create_next_population (CROMOSSOMA*a, CROMOSSOMA*b);

//------------------FITNESS-------------------------//

void sort_cromo_by_fitness (POPULATION *population);

float fitness (CROMOSSOMA *cromo);

//------------------CROMOSSOMA-------------------------//

void insert_cromossomas (POPULATION *cromo, COUNTRY *temp_country);

//------------------CROSSOVER-------------------------//

void parent_selection (POPULATION *population, int elitism_amount);

CROMOSSOMA* fitness_proportional_selection (POPULATION *population);


//------------------GENE-------------------------//

void insert_gene (CROMOSSOMA *cromo, COUNTRY *arr_of_countries);

//------------------ALLOCATE-------------------------//

POPULATION *allocate_memory_population();

CROMOSSOMA *allocate_memory_cromossomas(int size);

GENE *allocate_memory_genes(int size);

//------------------AUX-------------------------//

void shuffle_genes (CROMOSSOMA *cromo, int size);

float euclidean_dist (GENE* first, GENE *second);

void swap_cromo (CROMOSSOMA *a, CROMOSSOMA *b);

float sum_population_fitness (POPULATION *population);

#endif //TSP_AG_H
