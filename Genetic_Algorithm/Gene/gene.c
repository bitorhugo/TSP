//
// Created by Vitor Hugo on 28/12/2021.
//

#include "gene.h"
#include <stdlib.h>

GENE *allocate_memory_gene(int size) {
    GENE *new_gene = calloc(size, sizeof(GENE));
    return new_gene;
}