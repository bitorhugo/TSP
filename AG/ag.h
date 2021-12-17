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

typedef struct chromosomes {
    GENE *genes;
    int num_of_genes;
    float fitness_value;
}CHROMOSOME;

typedef struct population {
    CHROMOSOME *chromosomes;
    int num_of_chromosomes;
}POPULATION;

typedef struct generation {
    uint32_t id;
    POPULATION *parent;
    POPULATION *child;
    CHROMOSOME *fittest_chromosomes;
    struct generation *next_generation;
}GENERATION;

//------------------AG-------------------------//

void intialize_genetic_algorithm (COUNTRY *country, int num_of_iterations, int size_of_population, int num_elitism, float mutation_probability);

//------------------GENERATION-------------------------//

GENERATION* insert_generation (GENERATION **head, bool at_head);

GENERATION* search_generation (GENERATION **head, uint32_t generation_id);

GENERATION* search_generation_via_fitness (GENERATION **head, int fitness_value);

//------------------POPULATION-------------------------//

POPULATION* create_initial_population (COUNTRY *country_to_visit, int size_of_population);

void insert_population(POPULATION *population, COUNTRY *temp_country, int size_of_population);

POPULATION* create_next_population (POPULATION *old_population, int elitism_amount, float mutation_prob);

//------------------CROMOSSOMA-------------------------//

void insert_cromossomas (POPULATION *chromo, COUNTRY *temp_country);

void insert_fittest_chromosomes (GENERATION *generation);

//------------------GENE-------------------------//

void insert_gene (CHROMOSOME *cromo, COUNTRY *arr_of_countries);

//------------------CROSSOVER-------------------------//

CHROMOSOME * cross_over (CHROMOSOME *parent_one,CHROMOSOME *parent_two);

void parent_selection (POPULATION *population, int elitism_amount);

CHROMOSOME * fitness_proportional_selection (POPULATION *population);

//------------------FITNESS-------------------------//

void sort_cromo_by_fitness (POPULATION *population);

float fitness (CHROMOSOME *chromo);

//------------------MUTATION-------------------------//

void mutation (POPULATION * population, float mutation_prob);

//------------------ALLOCATE-------------------------//

GENERATION* allocate_memory_generation();

POPULATION *allocate_memory_population();

CHROMOSOME *allocate_memory_cromossomas(int size);

GENE *allocate_memory_genes(int size);

//------------------AUX-------------------------//

void shuffle_genes (CHROMOSOME *cromo, int size);

float euclidean_dist (GENE* first, GENE *second);

void swap_cromo (CHROMOSOME *a, CHROMOSOME *b);

void swap_gene (GENE *a, GENE *b);

float sum_population_fitness (POPULATION *population);

int random_non_reapeting_number (int min_value, int max_value);

int is_generation_list_empty(GENERATION **head);

void free_generation_list (GENERATION **head);

#endif //TSP_AG_H
