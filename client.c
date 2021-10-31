//
// Created by Vitor Hugo on 31/10/2021.
//

#include "client.h"


Client *genesis = NULL;

void print_list() {
    Client *ptr = genesis;
    while (ptr != NULL) {
        printf("%d ", ptr->user_id);
        ptr = (Client *) ptr->next_client;
    }
}

void insert_client(uint32_t id) {



}
