//
// Created by Vitor Hugo on 08/01/2022.
//

#include "test_client_list.h"


int main_client_list_test (CLIENT_LL *list) {

    // insert client in list
    insert_client(list, false, "Toni", 23, "Rua das Flores Porto", 913673456, 12, 6, 1999);
    insert_client(list, false, "Teresa", 35, "Rua 9 de abril Porto", 932645812, 8, 12, 1989);
    insert_client_sorted(list, "Afonso", 26, "Rua Telheiro 89 Matosinhos", 914678345, 21, 4, 1996);
    // remove client in list
    remove_client(list, "Teresa");
    // search for client in list
    search_client(list, "Toni");
    // print all clients in list
    print_clients(list);
    // sort clients
    sort_clients(list);
    // print all clients
    print_clients(list);

    return 0;
}