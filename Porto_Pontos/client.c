//
// Created by Vitor Hugo on 31/10/2021.
//

#include "client.h"

//------------------CLIENT-------------------------//
/*
void insert_new_client (CLIENT **head, bool at_head, uint32_t client_id) {

    if (is_list_empty(head)) at_head = true;

    CLIENT *new_client = allocate_memory_Client(); // allocates memory for new client
    new_client->user_id = client_id;

    if (at_head) {
        new_client->next_client = *head; // stores head pointer in new client
        *head = new_client; //
        printf("New client head at %p\tnext_client: %p\n", new_client, new_client->next_client);
    } else {
        CLIENT *temp = *head;
        while (temp->next_client != NULL) { // Moves through linked list until last current client found
            temp = temp->next_client;
        }
        // inserts new client at the end and restores link
        temp->next_client = new_client;
        new_client->next_client = NULL;
        printf("New client tail at %p\tnext_client: %p\n", new_client, new_client->next_client);
    }
}

void insert_new_client_head (CLIENT **head) {
    CLIENT *new_client = allocate_memory_Client(); // allocates memory for new client
    new_client->next_client = *head; // stores head pointer in new client
    *head = new_client; //
    printf("New client head at %p\tnext_client: %p\n", new_client, new_client->next_client);
}

void insert_new_client_tail (CLIENT **head) {
    CLIENT *new_client = allocate_memory_Client();

    if (is_list_empty(head)) {
        *head = new_client;
        new_client->next_client = NULL;
        printf("New client at %p\tnext_client: %p\n", new_client, new_client->next_client);
        return;
    }

    CLIENT *temp = *head;
    while (temp->next_client != NULL) { // Moves through linked list until last current client found
        temp = temp->next_client;
    }
     // inserts new client at the end and restores link
    temp->next_client = new_client;
    new_client->next_client = NULL;

    printf("New client tail at %p\tnext_client: %p\n", new_client, new_client->next_client);
}

void insert_new_client_sorted (CLIENT **head, uint32_t client_id) {
    CLIENT *new_client = allocate_memory_Client();
    new_client->user_id = client_id;
    if (is_list_empty(head)) {
        *head = new_client;
        printf("New client %d at %p\tnext_client: %p\n", new_client->user_id, new_client, new_client->next_client);
        return;
    }
    else {
        sort_clients(head, 0);
        CLIENT *temp_client = *head;
        if (temp_client->user_id > client_id) {
            new_client->next_client = *head;
            *head = new_client;
            return;
        }
        while (temp_client != NULL) {
            if (temp_client->next_client == NULL) {
                temp_client->next_client = new_client;
                return;
            } // if next_client == NULL insert at tail
            if (temp_client->next_client->user_id > client_id) {
                CLIENT *temp_swap = temp_client->next_client;
                temp_client->next_client = new_client;
                new_client->next_client = temp_swap;
                return;
            } // perform a swap to maintain linkage between clients
            temp_client = temp_client->next_client;
        }
    }
}

void remove_client (CLIENT **head, uint32_t userid_to_delete) {
    if (is_list_empty(head)) {
        fprintf(stderr, "ERROR: NO CLIENTS AVAILABLE.\n");
        exit(1);
    }

    CLIENT *temp = *head; // temp = memory addr of head

    while (temp != NULL) { // goes through linked list until the end
        if (temp->user_id == userid_to_delete && temp == *head) { // checks if head is client to be deleted
            *head = temp->next_client;
            free (temp);
            return;
        }
        if (temp->next_client->user_id == userid_to_delete) {
            temp->next_client = temp->next_client->next_client;
            free (temp->next_client);
            return;
        }
        temp = temp->next_client;
    }

    printf("Client %d not found.\n", userid_to_delete);
}

CLIENT *search_client_by_id (CLIENT **head, uint32_t userid_to_search) {
    if (is_list_empty(head)) {
        fprintf(stderr, "ERROR: NO CLIENTS AVAILABLE\n");
    }

    CLIENT* temp = *head;
    while (temp != NULL) {
        if (temp->user_id == userid_to_search) {
            printf("Client with id %d found at %p\n", userid_to_search, temp);
            return temp;
        }
        else temp = temp->next_client;
    }
    printf("Client %d not found.\n", userid_to_search);
    return NULL;
}

void sort_clients (CLIENT **head, short attribute) {
    if (is_list_empty(head)) {
        fprintf(stderr, "ERROR: NO CLIENTS AVAILABLE\n");
        return;
    }
    if (attribute == 0) sort_clients_id(head);
    else sort_clients_name(head);
}

void sort_clients_id (CLIENT **head) {

    time_t start = 0, end = 0;
    time(&start);

    CLIENT *temp_client = *head;
    CLIENT * a;
    CLIENT * b;

    if (temp_client->next_client == NULL) return;

    FrontBackSplit(temp_client, &a, &b);

    sort_clients_id(&a);
    sort_clients_id(&b);

    *head = SortedMerge(a, b);

    time(&end);
    printf("Time elapsed: %.5lf\n", difftime(end, start));

}

void sort_clients_name (CLIENT **head) {
}

void print_clients (CLIENT **head) {
    if (is_list_empty(head)) {
        fprintf(stderr, "ERROR: NO CLIENTS AVAILABLE\n");
        return;
    }

    CLIENT *temp = *head;
    while (temp != NULL) {
        printf("Client %d at %p\n", temp->user_id, temp);
        temp = temp->next_client;
    }
}
*/
//------------------Allocate-------------------------//

CLIENT * allocate_memory_Client () {
    CLIENT *new_client = calloc(1, sizeof(CLIENT));
    if (new_client == NULL)
        fprintf(stderr, "Not able to allocate memory\n");

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

int is_list_empty (CLIENT **head) {
    if (*head == NULL) return 1;
    else return 0;
}

void free_clients_list (CLIENT **head) {

    CLIENT *temp = NULL;

    while (*head != NULL) {
        temp = *head;
        *head = temp->next_client;
        free(temp);
    }

}

//------------------FILES-------------------------//

void write_report (CLIENT **head, uint32_t client_id, bool is_binary) {


}

//------------------AUX-------------------------//

void FrontBackSplit(CLIENT * source, CLIENT ** frontRef, CLIENT ** backRef) {
    CLIENT *fast;
    CLIENT *slow;
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

CLIENT *SortedMerge(CLIENT *a, CLIENT *b) {
    CLIENT * result = NULL;

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

float float_rand (float min, float max) {
    float scale = rand() / (float) RAND_MAX; /* [0, 1.0] */
    return min + scale * (max - min);      /* [min, max] */
}

int int_rand (int min, int max) {
    int num = (rand() % (max - min + 1)) + min;
    return num;
}