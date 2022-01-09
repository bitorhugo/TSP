//
// Created by Vitor Hugo on 28/12/2021.
//

#ifndef TSP_GENE_H
#define TSP_GENE_H

typedef struct gene {
    int id;
    float x;
    float y;
} GENE;

/**
 * allocates memory for a gene array
 * @param size array size
 * @return address of gene array
 */
GENE *allocate_memory_gene(int size);

#endif //TSP_GENE_H
