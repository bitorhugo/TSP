//
// Created by Vitor Hugo on 31/10/2021.
//

#include "client.h"

/*
 * A -> B -> C -> NULL
 */


/*
 * 1 - allocates memory to new client
 * 2 - new client points to first client (head)
 * 3 - head points to new client
 */
void insert_new_client_head (Client **head) {
    Client *new_client = allocate_memory_Client(); // allocates memory for new client
    new_client->next_client = *head; // stores head pointer in new client
    *head = new_client; //
    printf("New client head at %p\tnext_client: %p\n", new_client, new_client->next_client);
}

/*
 * 1 - allocated memory to new client
 * 2 - checks if linked list is empty
 * 2.1 - if tail will become head of linked list
 * 2.2 - else goes to last client in the link
 * 3 - changes pointer in last client from NULL to new clients' address
 * 4 - points new client next_client to NULL
 */
void insert_new_client_tail (Client **head) {
    Client *new_client = allocate_memory_Client();
    new_client->next_client = NULL;

    if (is_list_empty(head)) {
        *head = new_client;
        new_client->next_client = NULL;
        printf("New client tail at %p\tnext_client: %p\n", new_client, new_client->next_client);
        return;
    }

    Client *temp = *head;
    while (temp->next_client != NULL) { // Moves through linked list until last current client found
        temp = temp->next_client;
    }
     // inserts new client at the end and restores link
    temp->next_client = new_client;
    new_client->next_client = NULL;

    printf("New client tail at %p\tnext_client: %p\n", new_client, new_client->next_client);
}

/*
 * 1 - check if list is empty
 * 2 - Searches list until current client next_client->userid == userid_to_delete
 * 3 - if found points current client next_client to next_client->next_client
 * 4 - frees memory from wanted client
 */
void remove_client (Client **head, uint32_t userid_to_delete) {
    if (is_list_empty(head)) {
        fprintf(stderr, "ERROR: NO CLIENTS AVAILABLE.\n");
        exit(1);
    }

    Client *temp = *head; // temp = memory addr of head

    while (temp != NULL) { // goes through linked list until the end
        if (temp->user_id == userid_to_delete && temp == *head) { // checks if head is client to be deleted
            *head = temp->next_client;
            free (temp);
            return;
        }
        else if (temp->next_client->user_id == userid_to_delete) {
            temp->next_client = temp->next_client->next_client;
            free (temp->next_client);
            return;
        }
        else temp = temp->next_client;
    }

    printf("Client %d not found.\n", userid_to_delete);
}

/*
 * 1 - checks if list is empty
 * 2 - searches list for wanted userid
 * 3 - prints wanted client address
 */
void search_client_by_id (Client **head, uint32_t userid_to_search) {
    if (is_list_empty(head)) {
        fprintf(stderr, "ERROR: NO CLIENTS AVAILABLE\n");
    }

    Client* temp = *head;
    while (temp != NULL) {
        if (temp->user_id == userid_to_search) {
            printf("Client with id %d found at %p\n", userid_to_search, temp);
            return;
        }
        else temp = temp->next_client;
    }
    printf("Client %d not found.\n", userid_to_search);
}

/*
 * 1 - checks if list is empty
 * 2 - prints clients id and address until client next_client == NULL
 */
void print_clients (Client **head) {
    if (is_list_empty(head)) {
        fprintf(stderr, "ERROR: NO CLIENTS AVAILABLE\n");
        return;
    }

    Client *temp = *head;
    while (temp != NULL) {
        printf("Client %d at %p\n", temp->user_id, temp);
        temp = temp->next_client;
    }
}

/*
 * 1 - Checks file available to open
 * 2 - reads each file segment to line array
 * 3 - copies from line array to client
 * 4 - closes file
 */
void read_clients_from_file (Client **head) {

    FILE *file;
    file = fopen("readme.txt", "r");
    char line_of_file[FILE_LINE_SIZE];

    if (file == NULL) exit(1);

}

void sort_clients_VAT (Client **head) {

    if (is_list_empty(head)) {
        fprintf(stderr, "NO CLIENTS AVAILABLE.\n");
        return;
    }





}

/*
 * 1 - checks if trips array is empty
 * 1.2 - if empty, allocate memory
 * 2 - insert trip
 */
void create_trip_for_client (Client **head, uint32_t client_id, char* country_name) {

    if (is_list_empty(head)) {
        fprintf(stderr, "ERROR: NO CLIENTS AVAILABLE\n");
        return;
    }

    Client *temp = *head;

    while (temp != NULL) {
        if (temp->user_id == client_id) {
            if (temp->trips_to_be_made == NULL) {
                // allocates memory for country_name
                temp->trips_to_be_made = allocate_memory_trips(strlen(country_name));
            }
            // TODO: ASK TEACHER ABOUT MEMORY USAGE, MAY NEED TO USE REALLOC
            else {
                temp->trips_to_be_made = realloc(
                        temp->trips_to_be_made,
                        strlen(temp->trips_to_be_made) + strlen(country_name));

                strcat(temp->trips_to_be_made, country_name);
                strcat(temp->trips_to_be_made, " ");
            }

            return;
        }
    }

}

Client* allocate_memory_Client () {
    Client *new_client = malloc(sizeof(Client));
    if (new_client == NULL) {
        fprintf(stderr, "Not able to allocate memory\n");
        exit(1);
    }
    return new_client;
}

char* allocate_memory_trips (int size) {
    char* trips = malloc(sizeof (char) * (size + 1)); // .. + 1 == Adds byte for '\0'
    if (trips == NULL) fprintf(stderr, "Not able to allocate memory\n");
    return trips;
}


int is_list_empty (Client **head) {
    if (*head == NULL) return 1;
    else return 0;
}

void free_clients_list (Client **head) {

    Client *i = *head;
    Client *j;
    for (j = i; j != NULL; i = j->next_client) {

        free (i);

    }
}

