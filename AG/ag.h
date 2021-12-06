//
// Created by Vitor Hugo on 28/11/2021.
//
#include "client.h"


#ifndef TSP_AG_H
#define TSP_AG_H
typedef struct gene {
    float x;
    float y;
}GENE;

typedef struct cromossoma {
    GENE *genes;
    int num_of_genes;
}CROMOSSOMA;

typedef struct population {
    CROMOSSOMA *cromossomas;
    int num_of_cromossomas;
}POPULATION;

//-----------------//

void create_population (Client **head, POPULATION *population, uint32_t client_id, int size_of_population);

void insert_population(POPULATION *population, Country* temp_country, int size_of_population);

void insert_cromossomas (POPULATION *cromo, Country *temp_country);

void insert_gene (CROMOSSOMA *cromo, Country *arr_of_countries);

POPULATION *allocate_memory_population();
CROMOSSOMA *allocate_memory_cromossomas(int size);
GENE *allocate_memory_genes(int size);

POPULATION *realloc_memory_population(POPULATION *population, int size);

#endif //TSP_AG_H
