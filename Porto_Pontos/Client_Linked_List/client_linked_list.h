//
// Created by Vitor Hugo on 27/12/2021.
//

#include "Client_Node/client_node.h"

#include <stdbool.h>

#ifndef TSP_CLIENT_LINKED_LIST_H
#define TSP_CLIENT_LINKED_LIST_H

/*
 * A linked list is represented by a pointer to the first node of the linked list.
 * The first node is called the head.
 * If the linked list is empty, then the value of the head is NULL.
 */

typedef struct client_linked_list {
    CLIENT_NODE *head;
    int list_size;
}CLIENT_LL;


void insert_client (CLIENT_LL *list, bool at_head, CLIENT client);
CLIENT search_client (CLIENT_LL *list, CLIENT client);
void remove_client (CLIENT_LL *list, CLIENT client);
void print_clients (CLIENT_LL *list);
void sort_clients (CLIENT_LL *list, short attribute);
void deallocate_client_linked_list (CLIENT_LL *list);

#endif //TSP_CLIENT_LINKED_LIST_H
