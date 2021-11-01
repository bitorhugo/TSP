//
// Created by Vitor Hugo on 31/10/2021.
//

#include "client.h"


Client *post_new_client(Client **head, uint32_t id) {
    Client *new_client = allocate_memory_Client();
    new_client->next_in_line = NULL;
    new_client->user_id = id;
    if (new_client->user_id == 0) { // if first client is inserted point head at him
        *head = new_client;
    }
    printf("New client at %p\thead at %p\n", new_client, *head);

    return new_client;

}

void insert_new_client_head(Client **head) {
    Client *new_client = allocate_memory_Client();
    new_client->next_in_line = *head;
    *head = new_client;
    printf("New client head at %p\tnext_in_line: %p\n", new_client, new_client->next_in_line);
}

void insert_new_client_tail(Client **head) {
    Client *new_client = allocate_memory_Client();
    new_client->next_in_line = NULL;

    //Check if head is NULL --> if is first client
    if (*head == NULL) {
        *head = new_client;
        return;
    }

    Client *temp = *head;
    while (temp->next_in_line != NULL) {
        temp = temp->next_in_line; // copies next Client to temp
    }
    temp->next_in_line = new_client; // restores linkage

    printf("New client tail at %p\tnext_in_line: %p\n", new_client, new_client->next_in_line);
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

Client* allocate_memory_Client() {
    Client *new_client = malloc(sizeof(Client));
    if (new_client == NULL) {
        printf("Not able to allocate memory\n");
    }
    return new_client;
}

