//
// Created by Vitor Hugo on 27/12/2021.
//

#include "client_linked_list.h"

#include <stdio.h>

void insert_client (CLIENT_LL *list, bool at_head, CLIENT client) {
    if (list->list_size < 1) {
        list->head = allocate_memory_node_client(client);
        list->list_size = 1;
    }
    else {
        CLIENT_NODE *new_node = allocate_memory_node_client(client);
        if (at_head) {
            new_node->next_node = list->head;
            list->head = new_node;
            list->list_size += 1;
        }
        else {
            CLIENT_NODE *temp_node = list->head;
            while (temp_node->next_node != NULL) {
                temp_node = temp_node->next_node;
            }
            temp_node->next_node = new_node;
            list->list_size += 1;
        }
    }
}

CLIENT search_client (CLIENT_LL *list, CLIENT client) {

    CLIENT_NODE *temp_node = list->head;
    while (temp_node != NULL) {
        if (temp_node->client.VAT == client.VAT){
            printf("Client %d found\n", temp_node->client.VAT);
            return temp_node->client;
        }
        temp_node = temp_node->next_node;
    }
    fprintf(stderr, "ERROR: CLIENT NOT FOUND\n");
    CLIENT null = {0};
    return null;
}

void remove_client (CLIENT_LL *list, CLIENT client) {
    if (list->list_size < 1) {
        fprintf(stderr, "ERROR: NO CLIENTS AVAILABLE\n");
        return;
    }
    CLIENT_NODE *temp_node = list->head;
    while (temp_node != NULL) {
        if (temp_node->client.VAT == client.VAT) { // checks if head is to be removed
            list->head = temp_node->next_node;
            deallocate_memory_node_client(temp_node);
            list->list_size -= 1;
            return;
        }
        if (temp_node->next_node->client.VAT == client.VAT) {
            temp_node->next_node = temp_node->next_node->next_node;
            deallocate_memory_node_client(temp_node->next_node);
            list->list_size -= 1;
            return;
        }
        temp_node = temp_node->next_node;
    }
    fprintf (stderr, "ERROR: CLIENT NOT FOUND\n");
}

void print_clients (CLIENT_LL *list) {
    if (list->list_size < 1) {
        fprintf(stderr, "ERROR: NO CLIENTS AVAILABLE\n");
    }
    CLIENT_NODE *temp_node = list->head;
    while (temp_node != NULL) {
        printf ("Client %d\n", temp_node->client.VAT);
        temp_node = temp_node->next_node;
    }
}

void deallocate_client_linked_list (CLIENT_LL *list) {
    free(list);
}
