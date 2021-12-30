//
// Created by Vitor Hugo on 27/12/2021.
//
#include "Client/client.h"

#ifndef TSP_CLIENT_NODE_H
#define TSP_CLIENT_NODE_H


typedef struct client_node {
    CLIENT client;
    struct client_node *next_node;
}CLIENT_NODE;

CLIENT_NODE* allocate_memory_node_client ();

void deallocate_memory_node_client (CLIENT_NODE *node);

CLIENT create_client (char *name, uint32_t VAT, char *address, uint32_t phone_number, int birth_day, int birth_month, int birth_year);

#endif //TSP_CLIENT_NODE_H
