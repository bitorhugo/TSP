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
void insert_new_client_head(Client **head) {
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
void insert_new_client_tail(Client **head) {
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
 * TODO: BEFORE DELETING CHECK IF CLIENT TO BE DELETED IS HEAD OR TAIL OF LINK
 */
void remove_client (Client **head, uint32_t userid_to_delete) {
    if (is_list_empty(head)) {
        fprintf(stderr, "ERROR: NO CLIENTS AVAILABLE.\n");
        exit(1);
    }

    Client *temp = *head; // temp = memory addr of head

    while (temp != NULL) { // goes through linked list until the end
        if (temp->user_id == userid_to_delete) { // checks if next client is equals id being searched
                temp->next_client = temp->next_client->next_client; // removes wanted client from link
                free(temp->next_client); // frees memory alloc from wanted client
                return;
        }
        temp = temp->next_client;
    }

    printf("Client %d not found.\n", userid_to_delete);
}

/*
 * 1 - checks if list is empty
 * 2 - searches list for wanted userid
 * 3 - prints wanted client address
 */
void search_client_by_id (Client **head, uint32_t userid_to_search) {
    if (*head == NULL) {
        fprintf(stderr, "ERROR: NO CLIENTS AVAILABLE\n");
    }

    Client* temp = *head;
    while (temp->next_client != NULL) {
        if (temp->user_id == userid_to_search) printf("Client with id %d found at %p\n",
                                                     userid_to_search, temp);
        temp = temp->next_client;
    }

    printf("Client %d not found.\n", userid_to_search);
}

/*
 * 1 - checks if list is empty
 * 2 - prints clients id and address until client next_client == NULL
 */
void print_clients(Client **head) {
    if (is_list_empty(head)) {
        fprintf(stderr, "ERROR: NO CLIENTS AVAILABLE\n");
        return;
    }
    int *i;
    Client *temp = *head;
    while (temp->next_client != NULL) {
        printf("Client %d at %p\n", temp->user_id, temp);
        temp = temp->next_client;
    }
    printf("Client %d found at %p\n", temp->user_id, temp);
}

void read_clients_from_file(Client *head) {

    FILE *file;
    file = fopen("readme.txt", "r");
    char line_of_file[FILE_LINE_SIZE];

    if (file == NULL) exit(1);

    while (!feof(file)) {
        fgets(line_of_file, sizeof(line_of_file), file);

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

int is_list_empty (Client **head) {
    if (*head == NULL) return 1;
    else return 0;
}

