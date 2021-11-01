//
// Created by Vitor Hugo on 31/10/2021.
//

#include "client.h"

/*
 * A -> B -> C -> NULL
 */

Client *post_new_client(Client **head, uint32_t id) {
    Client *new_client = allocate_memory_Client();
    new_client->next_client = NULL;
    new_client->user_id = id;
    if (new_client->user_id == 0) { // if first client is inserted point head at him
        *head = new_client;
    }
    printf("New client at %p\thead at %p\n", new_client, *head);

    return new_client;

}

void insert_new_client_head(Client **head) {
    Client *new_client = allocate_memory_Client();
    new_client->next_client = *head; // D -> A
    *head = new_client; // head -> D
    printf("New client head at %p\tnext_client: %p\n", new_client, new_client->next_client);
}

void insert_new_client_tail(Client **head) {
    Client *new_client = allocate_memory_Client();
    new_client->next_client = NULL;

    //Check if head is NULL --> if is first client
    if (*head == NULL) {
        *head = new_client;
        return;
    }

    Client *temp = *head;
    while (temp->next_client != NULL) {
        temp = temp->next_client; // copies next Client to temp
    }
    temp->next_client = new_client; // restores linkage

    printf("New client tail at %p\tnext_client: %p\n", new_client, new_client->next_client);
}

void print_clients(Client *client) {
    if (client == NULL) {
        printf("No clients available\n");
        return;
    }
    while(client != NULL) {
        printf("Client at %p\tnext client at %p\n", client, client->next_client);
        client = client->next_client;
    }
}

Client* allocate_memory_Client() {
    Client *new_client = malloc(sizeof(Client));
    if (new_client == NULL) {
        fprintf(stderr, "Not able to allocate memory\n");
        exit(1);
    }
    return new_client;
}

