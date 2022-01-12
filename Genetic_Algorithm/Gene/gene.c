//
// Created by Vitor Hugo on 28/12/2021.
//

#include "gene.h"
#include <stdlib.h>

GENE *allocate_memory_gene(int size) {
    GENE *new_gene = calloc(size, sizeof(GENE));
    return new_gene;
}

void deallocate_memory_gene(GENE *gene) {
    free(gene);
}

void swap_gene(GENE *a, GENE *b) {
    GENE temp = *a;
    *a = *b;
    *b = temp;
}