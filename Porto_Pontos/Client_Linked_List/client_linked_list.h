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

/**
 * insert a client from the linked list
 * @param list linked list
 * @param at_head head of linked list
 * @param client client to insert
 */
void insert_client (CLIENT_LL *list, bool at_head, CLIENT client);
/**
 * searches for a client from the linked list
 * @param list linked list
 * @param client_name clients name
 * @return return client wanted
 */
CLIENT search_client (CLIENT_LL *list, const char *client_name);
/**
 * removes a client from the linked list
 * @param list linked list
 * @param client client wanted
 */
void remove_client (CLIENT_LL *list, CLIENT client);
/**
 * print all clients from linked list
 * @param list linked list
 */
void print_clients (CLIENT_LL *list);
/**
 * sorts clients from linked list
 * @param list linked list
 * @param attribute 0 -> by id || 1 -> by name
 */
void sort_clients (CLIENT_LL *list, short attribute);
/*
 * frees linked list
 */
void deallocate_client_linked_list (CLIENT_LL *list);

#endif //TSP_CLIENT_LINKED_LIST_H
