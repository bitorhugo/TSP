//
// Created by Vitor Hugo on 27/12/2021.
//

#include "client_node.h"


CLIENT_NODE* allocate_memory_node_client () {
    CLIENT_NODE *new_client = calloc(1, sizeof(CLIENT_NODE));
    return new_client;
}

void deallocate_memory_node_client (CLIENT_NODE *node) {
    free(node);
}

CLIENT create_client (char *name, uint32_t VAT, char *address, uint32_t phone_number, int birth_day, int birth_month, int birth_year) {
    CLIENT new_client = {0};

    new_client.name = name;
    new_client.VAT = VAT;
    new_client.address = address;
    new_client.phone_number = phone_number;
    new_client.birth = create_date(birth_day, birth_month, birth_year);
    new_client.registration = insert_registration_day();

    return new_client;
}