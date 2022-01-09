//
// Created by Vitor Hugo on 28/12/2021.
//

#include "Generation_Linked_List/generation_linked_list.h"

#ifndef TSP_MAIN_ALGORITHM_H
#define TSP_MAIN_ALGORITHM_H

/**
 * finds best route possible for client
 * @param booked_trip booked trip
 * @param num_iterations number of algo iterations
 * @param size_population population size
 * @param num_elitism elitism number
 * @param prob_mutation mutation probability
 */
void initialize_algorithm (const COUNTRY *booked_trip, int num_iterations, int size_population, int num_elitism, float prob_mutation);

#endif //TSP_MAIN_ALGORITHM_H
