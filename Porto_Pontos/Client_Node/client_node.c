//
// Created by Vitor Hugo on 27/12/2021.
//

#include "client_node.h"


CLIENT_NODE* allocate_memory_node_client (CLIENT client) {
    CLIENT_NODE *new_client = calloc(1, sizeof(CLIENT_NODE));
    new_client->client = client;
    return new_client;
}

void deallocate_memory_node_client (CLIENT_NODE *node) {
    free(node);
}