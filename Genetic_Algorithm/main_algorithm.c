//
// Created by Vitor Hugo on 28/12/2021.
//
#include "main_algorithm.h"
#include <stdio.h>


void initialize_algorithm (const COUNTRY *booked_trip, int num_iterations, int size_population, int num_elitism, float prob_mutation) {
    // create generation linked list
    GENERATION_LL list;

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
    generation.parent_population = insert_first_population(&generation, booked_trip, size_population);

    // insert child population
    generation.child_population = insert_child_population(&generation, num_elitism, prob_mutation);
 /*   insert_generation(&list, false, generation);

    for (size_t i = 1; i <= num_iterations; ++i) {

        generation.parent_population = insert_population(&generation, num_elitism, prob_mutation);
        generation.child_population = insert_population(&generation, num_elitism, prob_mutation);
    }
*/
}



