//
// Created by Vitor Hugo on 27/12/2021.
//

#include "client_linked_list.h"

#include <stdio.h>

/*
 * Private functions prototypes
 */
void sort_clients_id (CLIENT_LL *list);
void sort_clients_name (CLIENT_LL *list);
void FrontBackSplit(CLIENT_NODE * source, CLIENT_NODE ** frontRef, CLIENT_NODE ** backRef);

/*
 * Public functions implementation
 */
void insert_client (CLIENT_LL *list, bool at_head, char *name, uint32_t VAT, char *address, uint32_t phone_number, int birth_day, int birth_month, int birth_year) {
    if (list->list_size < 1) {
        list->head = allocate_memory_node_client();
        list->head->client = create_client(name, VAT, address, phone_number, birth_day, birth_month, birth_year);
        list->list_size = 1;
    }
    else {
        CLIENT_NODE *new_node = allocate_memory_node_client();
        new_node->client = create_client(name, VAT, address, phone_number, birth_day, birth_month, birth_year);

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
CLIENT search_client (CLIENT_LL *list, const char *client_name) {

    CLIENT_NODE *temp_node = list->head;
    while (temp_node != NULL) {
        if (temp_node->client.name == client_name){
            printf("Client %s found\n", temp_node->client.name);
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
void sort_clients (CLIENT_LL *list, short attribute) {
    if (list->list_size < 1) {
        fprintf(stderr, "ERROR: NO CLIENTS AVAILABLE\n");
        return;
    }
    if (attribute == 0) sort_clients_id(list);
    else sort_clients_name(list);
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
void save_client_txt (CLIENT_LL *list, char *filename) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        fprintf(stderr, "ERROR: NOT ABLE TO OPEN FILE FOR WRITING\n");
        return;
    }

    /*
     * FILE TEMPLATE:
     * Client 'name'
     * booked trips:
     * finished trips
    */

    fprintf (fp, "PORTO PONTOS CLIENTS\n");

    // iterate over every client
    CLIENT_NODE *temp_node = list->head;
    while (temp_node != NULL) {

        fprintf(fp, "Client %s:\n", temp_node->client.name);

        // iterate over clients booked trips
        if (temp_node->client.size_booked_trips > 1){
            fprintf(fp, "Booked trips: ");
            for (size_t i = 0; i < temp_node->client.size_booked_trips; ++i) {
                COUNTRY *temp_country = temp_node->client.booked_trips + i;
                if (i == temp_node->client.size_booked_trips - 1) {
                    fprintf(fp, "%s\n", temp_country->name);
                    break;
                }
                fprintf(fp, "\t%s, ", temp_country->name);
            }
        }

        // iterate over finished trips
        if (temp_node->client.size_finished_trips > 1) {
            fprintf(fp, "Finished trips: ");
            for (size_t i = 0; i < temp_node->client.size_finished_trips; ++i) {
                COUNTRY *temp_country = temp_node->client.finished_trips + i;
                if (i == temp_node->client.size_finished_trips - 1) {
                    fprintf(fp, "%s\n", temp_country->name);
                    break;
                }
                fprintf(fp, "\t%s, ", temp_country->name);
            }
        }

        fprintf(fp, "\n");

        temp_node = temp_node->next_node;
    }
}
void read_clients_txt (CLIENT_LL *list, char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "ERROR: NOT ABLE TO OPEN FILE FOR READING\n");
        return;
    }

    /*
     * FILE TEMPLATE
     * Number of clients: %d
     * Clients:
     *  'name'
     *  'VAT',
     *  'address',
     *  'phone_number',
     *  'birth (day/month/year),
     *  'registration' (day/month/year)',
     */

    // read number of clients
    fscanf(fp, "%*[^:] %*s %d", &list->list_size);

    for (size_t i = 0; i < list->list_size; ++i) {

        // save insert name
        char name [50] = "";
        fscanf(fp, "%s", name);

        // save VAT
        uint32_t vat = 0;
        fscanf(fp, "%d", &vat);

        // save address
        char address [100] = "";
        fscanf(fp, "%s", address);

        // save phone_number
        uint32_t phone_number = 0;
        fscanf(fp, "%d", &phone_number);

        // save birth (day/month/year)
        DATE birth = {0};
        fscanf(fp, "%d %*s %d %*s %d", &birth.day, &birth.month, &birth.year);

        // save registration
        DATE registration = {0};
        fscanf(fp, "%d %*s %d %*s %d", &registration.day, &registration.month, &registration.year);

        insert_client(list, false, name, vat, address, phone_number, birth.day, birth.month, birth.year);
    }

    fclose(fp);

}
void deallocate_client_linked_list (CLIENT_LL *list) {
    free(list);
}

/*
 * Private functions implementation
 */
void sort_clients_id (CLIENT_LL *list) {
    CLIENT_NODE *temp_client = list->head;
    CLIENT_NODE * a;
    CLIENT_NODE * b;

    // check that list is sortable
    if (list->head->next_node == NULL) return;

    FrontBackSplit(temp_client, &a, &b);
/*
    sort_clients_id(&a);
    sort_clients_id(&b);

    *head = SortedMerge(a, b);*/
}

void FrontBackSplit(CLIENT_NODE * source, CLIENT_NODE ** frontRef, CLIENT_NODE ** backRef) {
    CLIENT_NODE *fast;
    CLIENT_NODE *slow;
    slow = source;
    fast = source->next_node;

    /* Advance 'fast' two nodes, and advance 'slow' one node */
    while (fast != NULL) {
        fast = fast->next_node;
        if (fast != NULL) {
            slow = slow->next_node;
            fast = fast->next_node;
        }
    }

    /* 'slow' is before the midpoint in the list, so split it in two
    at that point. */
    *frontRef = source;
    *backRef = slow->next_node;
    slow->next_node = NULL;
}

void sort_clients_name (CLIENT_LL *list) {

}