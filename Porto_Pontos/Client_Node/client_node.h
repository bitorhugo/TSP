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

/**
 * allocates memory for a client node
 * @return client_node address
 */
CLIENT_NODE* allocate_memory_node_client ();
/**
 * frees client node
 * @param node client node
 */
void deallocate_memory_node_client (CLIENT_NODE *node);
/**
 * creates a client
 * @param name name
 * @param VAT VAT
 * @param address address
 * @param phone_number phone number
 * @param birth_day birth day
 * @param birth_month birth month
 * @param birth_year birth year
 * @return copy of client
 */
CLIENT create_client (char *name, uint32_t VAT, char *address, uint32_t phone_number, int birth_day, int birth_month, int birth_year);

#endif //TSP_CLIENT_NODE_H
