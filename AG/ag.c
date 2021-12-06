//
// Created by Vitor Hugo on 28/11/2021.
//

#include "ag.h"


POPULATION *initial_population = NULL;

void create_population (Client **head, POPULATION *population, uint32_t client_id, int size_of_population) {
    if (is_list_empty(head)) {
        fprintf (stderr, "ERROR: NO CLIENTS AVAILABLE\n");
        return;
    }

    Client *temp_client = *head;

    while (temp_client != NULL) {

        if (temp_client->user_id == client_id)
            insert_population(population, temp_client->trips_to_be_made, size_of_population);

        temp_client = temp_client->next_client;
    }

    fprintf(stderr, "ERROR: CLIENT NOT FOUND\n");

}

void insert_population(POPULATION *population, Country* arr_of_countries, int size_of_population) {
    if (population == NULL) {
        population = allocate_memory_population();
    }
    population->num_of_cromossomas = size_of_population;
    insert_cromossomas (population, arr_of_countries);

}

void insert_cromossomas (POPULATION *population, Country *arr_of_countries) {
    population->cromossomas = allocate_memory_cromossomas(population->num_of_cromossomas);

    CROMOSSOMA *temp_cromo = population->cromossomas;
    for (int i = 0; i < population->num_of_cromossomas; ++i) {
        temp_cromo += i;
        temp_cromo->num_of_genes = arr_of_countries->size_trip_cities;
        insert_gene (temp_cromo, arr_of_countries);
    }

}

void insert_gene (CROMOSSOMA *cromo, Country *arr_of_countries) {
    cromo->genes = allocate_memory_genes(cromo->num_of_genes);
    GENE *temp_gene = cromo->genes;
    City *temp_city = arr_of_countries->cities;
    for (int i = 0; i < cromo->num_of_genes; ++i) {
        temp_gene += i;
        temp_city += i;
        temp_gene->x = temp_city->coordinates->x;
        temp_gene->y = temp_city->coordinates->y;
    }

}

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

POPULATION *realloc_memory_population(POPULATION *population, int size) {
    population = realloc(population, size * sizeof(POPULATION));
    return population;
}

