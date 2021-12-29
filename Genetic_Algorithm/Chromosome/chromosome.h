//
// Created by Vitor Hugo on 28/12/2021.
//

#include "Client_Linked_List/client_linked_list.h"
#include "Gene/gene.h"

#ifndef TSP_CHROMOSOME_H
#define TSP_CHROMOSOME_H

typedef struct chromosome {
    GENE *genes;
    int num_genes;
    float fitness_value;
} CHROMOSOME;

CHROMOSOME* allocate_memory_chromosome (int size);
void insert_gene (CHROMOSOME *chromosome, const COUNTRY *booked_trip);
void shuffle_genes (CHROMOSOME *chromosome);
float calculate_fitness (CHROMOSOME *chromosome);

#endif //TSP_CHROMOSOME_H
