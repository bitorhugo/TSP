//
// Created by Vitor Hugo on 31/10/2021.
//

#include "client.h"


struct sClient *create_new_client(uint32_t id) {
    struct sClient *new_client = malloc(sizeof(new_client));
    new_client->next_in_line = NULL;
    new_client->user_id = id;
    printf("New client at %p\n", new_client);
    return new_client;
}

void print_client(struct sClient *client) {
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

