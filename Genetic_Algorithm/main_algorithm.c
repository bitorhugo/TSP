//
// Created by Vitor Hugo on 28/12/2021.
//
#include "main_algorithm.h"
#include <stdio.h>

/*
 * Private prototype
 */
void print_last_generation_route (GENERATION_LL *list);

/*
 * Public implementation
 */
void initialize_algorithm (const COUNTRY *booked_trip, int num_iterations, int size_population, int num_elitism, float prob_mutation) {
    // create generation linked list
    GENERATION_LL list = {0};

    if (size_population % 2 != 0 || size_population == 0) {
        fprintf (stderr, "ERROR: POPULATION SIZE MUST BE PAIR AND POSITIVE\n");
        return;
    }
    if (num_elitism % 2 != 0 || num_elitism >= booked_trip->num_of_cities) {
        fprintf(stderr, "ERROR: ELITISM NUMBER MUST BE PAIR AND SMALLER THAN NUMBER OF GENES\n");
        return;
    }

    // create generation
    GENERATION generation = {0};

    // insert first population
    generation.parent_population = insert_first_population(booked_trip, size_population);

    // insert child population
    generation.child_population = insert_child_population(&generation, num_elitism, prob_mutation);
    insert_generation(&list, false, generation);

    for (size_t i = 1; i <= num_iterations; ++i) {

        // next generation parent will be the same as last generation child
        generation.parent_population = generation.child_population;

        // insert child population
        generation.child_population = insert_child_population(&generation, num_elitism, prob_mutation);

        // set generation id value
        generation.id = i;

        // insert generation in linked list
        insert_generation(&list, false, generation);
    }

    // prints best route found
    print_last_generation_route(&list);

}

/*
 * Private implementation
 */
void print_last_generation_route (GENERATION_LL *list) {
    printf ("Best route to take: \n");
    GENERATION *last_generation = search_generation(list, list->list_size - 1);
    GENE *temp_gene;
    for (size_t i = 0; i < list->head->generation.parent_population.chromosomes->num_genes; ++i) {
        temp_gene = last_generation->parent_population.chromosomes->genes + i;
        printf("City %d (x: %.2f, y: %.2f)\n", temp_gene->id, temp_gene->x, temp_gene->y);
    }
}
