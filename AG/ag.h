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
    int id;
    POPULATION *parent;
    POPULATION *child;
    struct generation *next_generation;
}GENERATION;


void intialize_genetic_algorithm (COUNTRY *country, int num_of_iterations, int size_of_population, int num_elitism, float mutation_probability);

GENERATION* insert_generation (GENERATION **head, bool at_head);
//------------------POPULATION-------------------------//

POPULATION* create_initial_population (COUNTRY *country_to_visit, int size_of_population);

void insert_population(POPULATION *population, COUNTRY *temp_country, int size_of_population);

POPULATION* create_next_population (POPULATION *old_population, int elitism_amount, float mutation_prob);

//------------------FITNESS-------------------------//

void sort_cromo_by_fitness (POPULATION *population);

float fitness (CROMOSSOMA *cromo);

//------------------CROMOSSOMA-------------------------//

void insert_cromossomas (POPULATION *cromo, COUNTRY *temp_country);

//------------------CROSSOVER-------------------------//

CROMOSSOMA* cross_over (CROMOSSOMA *parent_one,CROMOSSOMA *parent_two);

void parent_selection (POPULATION *population, int elitism_amount);

CROMOSSOMA* fitness_proportional_selection (POPULATION *population);

//------------------MUTATION-------------------------//

void mutation (POPULATION * population, float mutation_prob);

//------------------GENE-------------------------//

void insert_gene (CROMOSSOMA *cromo, COUNTRY *arr_of_countries);

//------------------ALLOCATE-------------------------//

GENERATION* allocate_memory_generation();

POPULATION *allocate_memory_population();

CROMOSSOMA *allocate_memory_cromossomas(int size);

GENE *allocate_memory_genes(int size);

//------------------AUX-------------------------//

void shuffle_genes (CROMOSSOMA *cromo, int size);

float euclidean_dist (GENE* first, GENE *second);

void swap_cromo (CROMOSSOMA *a, CROMOSSOMA *b);

void swap_gene (GENE *a, GENE *b);

float sum_population_fitness (POPULATION *population);

int random_non_reapeting_number (int min_value, int max_value);

int is_generation_list_empty(GENERATION_LIST **head);

#endif //TSP_AG_H
