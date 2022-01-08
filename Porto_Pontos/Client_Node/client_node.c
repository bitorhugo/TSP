//
// Created by Vitor Hugo on 27/12/2021.
//

#include "client_node.h"
#include <stdio.h>
#include <string.h>

void set_client_name (CLIENT *client, char *name);
void set_client_address (CLIENT *client, char *address);

CLIENT_NODE* allocate_memory_node_client () {
    CLIENT_NODE *new_client = calloc(1, sizeof(CLIENT_NODE));
    return new_client;
}

void deallocate_memory_node_client (CLIENT_NODE *node) {
    free(node);
}

CLIENT create_client (char *name, uint32_t VAT, char *address, uint32_t phone_number, int birth_day, int birth_month, int birth_year) {
    CLIENT new_client = {0};

    set_client_name(&new_client, name);
    new_client.VAT = VAT;
    set_client_address(&new_client, address);
    new_client.phone_number = phone_number;
    new_client.birth = create_date(birth_day, birth_month, birth_year);
    new_client.registration = insert_registration_day();

    return new_client;
}


void set_client_name (CLIENT *client, char *name) {
    client->name = allocate_memory_str(strlen(name));
    strcpy(client->name, name);
}
void set_client_address (CLIENT *client, char *address) {
    client->address = allocate_memory_str(strlen(address));
    strcpy(client->address, address);
}