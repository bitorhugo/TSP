//
// Created by Vitor Hugo on 31/10/2021.
//

#include "client.h"


Client *create_new_client(uint32_t id) {
    Client *new_client = malloc(sizeof(Client));
    if (new_client != NULL) { // Checks if program was able to allocate memory successfully
        new_client->next_in_line = NULL;
        new_client->user_id = id;
        printf("New client at %p\n", new_client);
    }
    else {
        printf("Not able to allocate memory");
    }
    return new_client;
}

void print_client(Client *client) {
    if (client == NULL) {
        printf("client is NULL\n");
    }
    else {
        printf("Client_ID: %d Client address: %p next_in_line address: %p\n",
               client->user_id,
               client,
               client->next_in_line);
    }
}

