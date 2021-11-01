//
// Created by Vitor Hugo on 31/10/2021.
//

#include "client.h"


Client *create_new_client(Client **head, uint32_t id) {
    Client *new_client = malloc(sizeof(Client));
    if (new_client != NULL) { // Checks if program was able to allocate memory successfully
        new_client->next_in_line = NULL;
        new_client->user_id = id;
        if (new_client->user_id == 1) { // if first client is inserted point head at him
            *head = new_client;
        }
        printf("New client at %p\n", new_client);
    }
    else {
        printf("Not able to allocate memory");
    }
    return new_client;
}

void print_client(Client **head, Client *client) {
    if (client == NULL) {
        printf("client is NULL\n");
    }
    else {
        printf("Client_ID: %d\tClient address: %p\tnext_in_line address: %p\tHead: %p\n",
               client->user_id,
               client,
               client->next_in_line,
               *head);
    }
}

