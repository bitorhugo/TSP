//
// Created by Vitor Hugo on 28/11/2021.
//

#include "ag.h"

//------------------POPULATION-------------------------//

POPULATION *create_initial_population (COUNTRY *country_to_visit, int size_of_population) {

    POPULATION *new_population = allocate_memory_population();
    new_population->num_of_cromossomas = size_of_population;
    insert_cromossomas (new_population, country_to_visit);
    sort_cromo_by_fitness(new_population);
    return new_population;
}

//------------------FITNESS-------------------------//

void sort_cromo_by_fitness (POPULATION *population) {

    CROMOSSOMA *a;
    CROMOSSOMA *b;
    for (int i = 0; i < population->num_of_cromossomas - 1; ++i) {
        for (int j = i + 1; j < population->num_of_cromossomas; ++j) {
            a = population->cromossomas + i;
            b = population->cromossomas + j;
            if (b->fitness_valeu > a->fitness_valeu)
                swap_cromo(a, b);
        }
    }

}

double fitness (CROMOSSOMA *cromo) {
    double sum = 0;
    GENE *temp_gene = cromo->genes;
    for (size_t i = 0; i < cromo->num_of_genes; ++i) {
        temp_gene += i;
        GENE *a = temp_gene;
        GENE *b = temp_gene + 1;
        if (i == cromo->num_of_genes - 1) // a = c0, b = c1, ..., a = c5, b = c0
            b = cromo->genes;
        sum += euclidean_dist(a, b);
    }
    return (1 / sum);
}

//------------------CROMO-------------------------//

void insert_cromossomas (POPULATION *population, COUNTRY *country) {
    population->cromossomas = allocate_memory_cromossomas(population->num_of_cromossomas);
    CROMOSSOMA *temp_cromo;
    for (int i = 0; i < population->num_of_cromossomas; ++i) {
        temp_cromo = population->cromossomas + i;
        temp_cromo->num_of_genes = country->size_trip_cities;
        insert_gene (temp_cromo, country);
        shuffle_genes(temp_cromo, temp_cromo->num_of_genes);
        temp_cromo->fitness_valeu = fitness(temp_cromo);
    }

}

void insert_gene (CROMOSSOMA *cromo, COUNTRY *arr_of_countries) {
    cromo->genes = allocate_memory_genes(cromo->num_of_genes);
    GENE *temp_gene;
    CITY *temp_city;
    for (int i = 0; i < cromo->num_of_genes; i++) {
        temp_gene = cromo->genes + i;
        temp_city = arr_of_countries->cities + i;
        temp_gene->id = i;
        temp_gene->x = temp_city->coordinates->x;
        temp_gene->y = temp_city->coordinates->y;
    }
}

//------------------ALLOCATE-------------------------//

POPULATION *allocate_memory_population() {
    POPULATION *new_pop = calloc(1, sizeof(POPULATION));
    if (new_pop == NULL) fprintf(stderr, "ERROR: NOT ABLE TO ALLOCATE MEMORY FOR POPULATION\n");
    return new_pop;
}

CROMOSSOMA *allocate_memory_cromossomas(int size) {
    CROMOSSOMA *new_cromo = calloc(size, sizeof(CROMOSSOMA));
    if (new_cromo == NULL) fprintf(stderr, "ERROR: NOT ABLE TO ALLOCATE MEMORY FOR CROMOSSOMA\n");
    return new_cromo;
}

GENE *allocate_memory_genes(int size) {
    GENE *new_gene = calloc(size, sizeof(GENE));
    if (new_gene == NULL) fprintf(stderr, "ERROR: NOT ABLE TO ALLOCATE MEMORY FOR GENE\n");
    return new_gene;
}

//------------------AUX-------------------------//

void shuffle_genes (CROMOSSOMA *cromo, int size) {
    if (size > 1) {
        for (size_t i = 0; i < size - 1; ++i) {
            size_t j = i + rand() / (RAND_MAX / (size - i) + 1);
            // swap
            GENE t = *(cromo->genes + j);
            *(cromo->genes + j) = *(cromo->genes + i);
            *(cromo->genes + i) = t;
        }
    }
}

double euclidean_dist (GENE* first, GENE *second) {
    return sqrt(pow(second->x - first->x, 2) + pow(second->y - first->y, 2));
}

void swap_cromo (CROMOSSOMA *a, CROMOSSOMA *b) {
    CROMOSSOMA temp = *a;
    *a = *b;
    *b = temp;
}

