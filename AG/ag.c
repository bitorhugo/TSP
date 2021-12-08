//
// Created by Vitor Hugo on 28/11/2021.
//

#include "ag.h"
/*
void create_population_t (POPULATION *population, Country *country_to_visit, int size_of_population) {

    if (population == NULL)
        population = allocate_memory_population();

    population->num_of_cromossomas = size_of_population;
    insert_cromossomas (population, country_to_visit);

}

void insert_cromossomas (POPULATION *population, Country *arr_of_countries) {
    population->cromossomas = allocate_memory_cromossomas(population->num_of_cromossomas);
    CROMOSSOMA *temp_cromo;
    for (int i = 0; i < population->num_of_cromossomas; ++i) {
        temp_cromo = population->cromossomas + i;
        temp_cromo->num_of_genes = arr_of_countries->size_trip_cities;
        insert_gene (temp_cromo, arr_of_countries);
    }
    shuffle_genes (population->cromossomas->genes, population->cromossomas->num_of_genes);
}

void insert_gene (CROMOSSOMA *cromo, Country *arr_of_countries) {
    cromo->genes = allocate_memory_genes(cromo->num_of_genes);
    GENE *temp_gene;
    City *temp_city;
    for (int i = 0; i < cromo->num_of_genes; i++) {
        temp_gene = cromo->genes + i;
        temp_city = arr_of_countries->cities + i;
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

void shuffle_genes (GENE *cromo, int size) {
    if (size > 1) {
        for (size_t i = 0; i < size; ++i) {
            size_t j = i + rand() / (RAND_MAX / (size - i) + 1);

            GENE t = *(cromo + j);
            *(cromo + j) = *(cromo + i);
            *(cromo + i) = t;
        }
    }
}
 */