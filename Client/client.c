//
// Created by Vitor Hugo on 31/10/2021.
//

#include "client.h"

//------------------CLIENT-------------------------//

void insert_new_client (Client **head, bool at_head, uint32_t client_id) {

    if (is_list_empty(head)) at_head = true;

    Client *new_client = allocate_memory_Client(); // allocates memory for new client
    //*(client_id) += 1;
    //uint32_t id_number = *client_id;

    if (at_head) {
        new_client->next_client = *head; // stores head pointer in new client
        *head = new_client; //
        new_client->user_id = client_id;
        printf("New client head at %p\tnext_client: %p\n", new_client, new_client->next_client);
    } else {
        Client *temp = *head;
        while (temp->next_client != NULL) { // Moves through linked list until last current client found
            temp = temp->next_client;
        }
        // inserts new client at the end and restores link
        temp->next_client = new_client;
        new_client->next_client = NULL;
        new_client->user_id = client_id;
        printf("New client tail at %p\tnext_client: %p\n", new_client, new_client->next_client);
    }
}

void insert_new_client_head (Client **head) {
    Client *new_client = allocate_memory_Client(); // allocates memory for new client
    new_client->next_client = *head; // stores head pointer in new client
    *head = new_client; //
    printf("New client head at %p\tnext_client: %p\n", new_client, new_client->next_client);
}

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

void sort_clients (Client **head, short attribute) {
    if (is_list_empty(head)) {
        fprintf(stderr, "ERROR: NO CLIENTS AVAILABLE\n");
        return;
    }
    if (attribute == 0) sort_clients_id(head);
    else sort_clients_name(head);
}

void sort_clients_id (Client **head) {

    time_t start = 0, end = 0;
    time(&start);

    Client *temp_client = *head;
    Client * a;
    Client * b;

    if (temp_client->next_client == NULL) return;

    FrontBackSplit(temp_client, &a, &b);

    sort_clients_id(&a);
    sort_clients_id(&b);

    *head = SortedMerge(a, b);

    time(&end);
    printf("Time elapsed: %.5lf\n", difftime(end, start));

}

void sort_clients_name (Client **head) {
}

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

void read_clients_from_file (Client **head) {

    FILE *file;
    file = fopen("readme.txt", "r");
    char line_of_file[FILE_LINE_SIZE];

    if (file == NULL) exit(1);

}

//------------------Allocate-------------------------//

Client* allocate_memory_Client () {
    Client *new_client = calloc(1, sizeof(Client));
    if (new_client == NULL) {
        fprintf(stderr, "Not able to allocate memory\n");
        exit(1);
    }
    return new_client;
}

char* allocate_memory_name (u_int64_t size) {
    char *names = calloc(size, sizeof(char));
    if (names == NULL) fprintf(stderr, "ERROR: NOT ABLE TO ALLOCATE MEMORY\n");
    return names;
}

//------------------Reallocate-------------------------//

char* realloc_memory_trip_name (char *trips, uint64_t size) {
    trips = realloc(trips, size);
    if (trips == 0) fprintf(stderr, "NOT ABLE TO REALLOCATE MEMORY\n");
    return trips;
}

//------------------Linked List-------------------------//

int is_list_empty (Client **head) {
    if (*head == NULL) return 1;
    else return 0;
}

void free_clients_list (Client **head) {

    Client *temp = NULL;

    while (*head != NULL) {
        temp = *head;
        *head = temp->next_client;
        free(temp);
    }

}

//------------------FILES-------------------------//

void write_report (Client **head, uint32_t client_id, bool is_binary) {
    if (is_list_empty(head)) {
        fprintf(stderr, "ERROR: NO CLIENTS AVAILABLE\n");
        return;
    }
    FILE *file_to_open;
    if (is_binary == true) file_to_open = fopen ("report_binary.bin", "wb");
    else  file_to_open =  fopen("report.txt", "w");

    if (file_to_open == NULL) {
        fprintf(stderr, "ERROR: FILE FAULT\n");
        return;
    }

    Client *temp_client = *head;
    while (temp_client != NULL) {

        fwrite(temp_client, sizeof(*temp_client), 1, file_to_open);

        temp_client = temp_client->next_client;
    }

    fclose(file_to_open);

}

//------------------AUX-------------------------//

void FrontBackSplit(Client* source, Client** frontRef, Client** backRef) {
    Client *fast;
    Client *slow;
    slow = source;
    fast = source->next_client;

    /* Advance 'fast' two nodes, and advance 'slow' one node */
    while (fast != NULL) {
        fast = fast->next_client;
        if (fast != NULL) {
            slow = slow->next_client;
            fast = fast->next_client;
        }
    }

    /* 'slow' is before the midpoint in the list, so split it in two
    at that point. */
    *frontRef = source;
    *backRef = slow->next_client;
    slow->next_client = NULL;
}

Client *SortedMerge(Client *a, Client *b) {
    Client* result = NULL;

    /* Base cases */
    if (a == NULL)
        return (b);
    else if (b == NULL)
        return (a);

    /* Pick either a or b, and recur */
    if (a->user_id <= b->user_id) {
        result = a;
        result->next_client = SortedMerge(a->next_client, b);
    }
    else {
        result = b;
        result->next_client = SortedMerge(a, b->next_client);
    }
    return (result);
}