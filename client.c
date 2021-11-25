//
// Created by Vitor Hugo on 31/10/2021.
//

#include "client.h"

/*
 * A -> B -> C -> NULL
 */

//------------------CLIENT-------------------------//

void insert_new_client (Client **head, short position, uint32_t *client_id) {

    if (is_list_empty(head)) position = 0;

    Client *new_client = allocate_memory_Client(); // allocates memory for new client
    *(client_id) += 1;
    uint32_t id_number = *client_id;

    if (position == 0) {
        new_client->next_client = *head; // stores head pointer in new client
        *head = new_client; //
        new_client->user_id = id_number;
        printf("New client head at %p\tnext_client: %p\n", new_client, new_client->next_client);
    } else {
        new_client->next_client = NULL;

        Client *temp = *head;
        while (temp->next_client != NULL) { // Moves through linked list until last current client found
            temp = temp->next_client;
        }
        // inserts new client at the end and restores link
        temp->next_client = new_client;
        new_client->next_client = NULL;
        new_client->user_id = id_number;
        printf("New client tail at %p\tnext_client: %p\n", new_client, new_client->next_client);
    }
}

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

//------------------TRIPS-------------------------//

/*
 * 1 - checks if trips array is empty
 * 1.2 - if empty, allocate memory
 * 2 - insert trip
 */
void insert_trip (Client **head, uint32_t client_id, char* country_name) {

    if (is_list_empty(head)) {
        fprintf(stderr, "ERROR: NO CLIENTS AVAILABLE\n");
        return;
    }

    //country_name = refactor_string_to_lower(country_name);

    Client *temp = *head; // temp for going through linked list
    while (temp != NULL) {
        if (temp->user_id == client_id) { // searches for wanted client

            insert_trip_name(temp, country_name);
            return;
        }
        temp = temp->next_client;
    }
    printf("Client not found\n");
}

/*
 * 1 - searches for wanted client
 * 2 - searches inside of client trips array for wanted trip
 * 3 - deletes wanted trip
 * 4 - reallocates memory for new trips array size
 */
void remove_trip (Client **head, uint32_t client_id, char* country_name) {

    if (is_list_empty(head)) {
        fprintf(stderr, "ERROR: NO CLIENTS AVAILABLE\n");
        return;
    }

    Client *temp = *head;

    while (temp != NULL) {
        if (temp->user_id == client_id) {
            for (int i = 0; i < temp->size_trips_to_be_made; ++i) {
                Country *temp3 = temp->trips_to_be_made + i;
                if (strcmp(temp3->name, country_name) == 0) {
                    for (int j = i; j < temp->size_trips_to_be_made; ++j) {
                        *(temp->trips_to_be_made + j) = *(temp->trips_to_be_made + j + 1);
                    }
                    temp->size_trips_to_be_made -= 1;
                    realloc_memory_trip(temp, temp->size_trips_to_be_made);
                    return;
                }
            }
        }
        temp = temp->next_client;
    }
    fprintf(stderr, "TRIP NOT FOUND\n");
}

/*
 * 1 - searches for wanted client
 * 2 - searches inside of clients trips array for wanted trip
 * 3 - edits wanted trip
 */
void edit_trip (Client **head, uint32_t client_id, char* country_name, char* new_country_name) {

    if (is_list_empty(head)) {
        fprintf(stderr, "ERROR: NO CLIENTS AVAILABLE\n");
        return;
    }

    Client *temp = *head;

    while (temp != NULL) {
        if (temp->user_id == client_id) {
            for (int i = 0; i < temp->size_trips_to_be_made; ++i) {
                Country *temp_country = temp->trips_to_be_made + i;
                if (strcmp(temp_country->name, country_name) == 0) {
                    realloc_memory_trip_name(temp_country->name, strlen(new_country_name));
                    strcpy(temp_country->name, new_country_name);
                    return;
                }
            }
        }
        temp = temp->next_client;
    }
}

/*
 * 1 - searches for wanted client
 * 2 - iterates over trips array
 * 3 - prints each trip made
 */
void print_trips (Client **head, uint32_t client_id) {

    if (is_list_empty(head)) {
        fprintf(stderr, "ERROR: NO CLIENTS AVAILABLE\n");
        return;
    }

    Client *temp = *head;

    while (temp != NULL) {
        if (temp->user_id == client_id) {
            if (temp->size_trips_to_be_made == 0) fprintf(stderr, "NO TRIPS FOUND\n");
            for (int i = 0; i < temp->size_trips_to_be_made; ++i) {
                Country *temp_country = temp->trips_to_be_made + i;
                printf("%s ", temp_country->name);
            }
            printf("\n");
            return;
        }
        temp = temp->next_client;
    }
    fprintf(stderr, "CLIENT NOT FOUND\n");
}

void insert_trip_name(Client *client, char *country_name) {
    if (client->trips_to_be_made == NULL) {
        client->trips_to_be_made = allocate_memory_trip();
        client->trips_to_be_made->name = allocate_memory_name(strlen(country_name));
        strcpy(client->trips_to_be_made->name, country_name);
        client->size_trips_to_be_made = 1;
    }
    else {
        client->trips_to_be_made = realloc_memory_trip(client, client->size_trips_to_be_made);
        Country *temp_country = client->trips_to_be_made + client->size_trips_to_be_made;
        temp_country->name = 0, temp_country->cities = 0, temp_country->size_trip_cities = 0; // TODO: ASK TEACHER FOR A BETTER WAY
        temp_country->name = allocate_memory_name(strlen(country_name));
        strcpy(temp_country->name, country_name);
        client->size_trips_to_be_made += 1;
    }
}

//------------------Cities-------------------------//

void insert_city (Client **head, uint32_t client_id, char *country_name, char *city_name) {

    if (is_list_empty(head)) {
        fprintf(stderr, "ERROR: NO CLIENTS FOUND\n");
        return;
    }

    Client *temp = *head;

    while (temp != NULL) {
        if (temp->user_id == client_id) {
            Country *temp_country;
            for (int i = 0; i < temp->size_trips_to_be_made; ++i) {
                temp_country = temp->trips_to_be_made + i;
                if (strcmp(temp_country->name, country_name) == 0) {
                        insert_city_name (temp_country, city_name); // Pass Country due to City not being allocated yet
                        return;
                }
            }
            fprintf(stderr, "TRIP NOT FOUND\n");
            return;
        }
        temp = temp->next_client;
    }
    fprintf(stderr, "ERROR: CLIENT NOT FOUND\n");
}

void remove_city (Client **head, uint32_t client_id, char *country_name, char *city_name) {

    if (is_list_empty(head)) {
        fprintf(stderr, "ERROR: NO CLIENTS AVAILABLE\n");
        return;
    }

    Client *temp = *head;
    while (temp != NULL) {
        if (temp->user_id == client_id) {
            Country *temp_country;
            for (int i = 0; i < temp->size_trips_to_be_made; ++i) {
                temp_country = temp->trips_to_be_made + i;
                if (strcmp(temp_country->name, country_name) == 0) {
                    City *temp_city;
                    for (int j = 0; j < temp_country->size_trip_cities; ++j) {
                        temp_city = temp_country->cities + j;
                        if (strcmp(temp_city->name, city_name) == 0) {
                            for (int k = 0; k < temp_country->size_trip_cities - j; ++k) {
                                *(temp_city + k) = *(temp_city + k + 1);
                            }
                            temp_country->size_trip_cities -= 1;
                            reallocate_memory_cities(temp_country, temp_country->size_trip_cities);
                            printf("City %s deleted\n", city_name);
                            return;
                        }
                    }
                    fprintf(stderr, "ERROR: CITY NOT FOUND\n");
                    return;
                }
            }
            fprintf(stderr, "ERROR: COUNTRY NOT FOUND\n");
            return;
        }
        temp = temp->next_client;
    }
    fprintf(stderr, "ERROR: CLIENT NOT FOUND\n");
}

void edit_city (Client **head, uint32_t client_id, char *country_name, char *city_name, char *new_city_name) {
    if (is_list_empty(head)) {
        fprintf(stderr, "ERROR: NO CLIENTS FOUND\n");
        return;
    }

    Client *temp_client = *head;

    while (temp_client != NULL) {

        if (temp_client->user_id == client_id) {

            Country *temp_country;
            for (int i = 0; i < temp_client->size_trips_to_be_made; ++i) {
                temp_country = temp_client->trips_to_be_made + i;
                if (strcmp(temp_country->name, country_name) == 0) {
                    City *temp_city;
                    for (int j = 0; j < temp_country->size_trip_cities; ++j) {
                        temp_city = temp_country->cities + j;
                        if (strcmp(temp_city->name, city_name) == 0) {
                            realloc_memory_trip_name(temp_city->name, strlen(new_city_name));
                            strcpy(temp_city->name, new_city_name);
                            return;
                        }
                    }
                }
            }

        }

        temp_client = temp_client->next_client;
    }
}

void search_city (Client **head, uint32_t client_id, char *country_name, char *city_name) {
    if (is_list_empty(head)) {
        fprintf(stderr, "ERROR: NO CLIENTS AVAILABLE\n");
        return;
    }
    Client *temp = *head;
    while (temp != NULL) {
        if (temp->user_id == client_id) {
            Country * temp_country;
            for (int i = 0; i < temp->size_trips_to_be_made; ++i) {
                temp_country = temp->trips_to_be_made + i;
                if (strcmp(temp_country->name, country_name) == 0) {
                    City *temp_city;
                    for (int j = 0; j < temp_country->size_trip_cities; ++j) {
                        temp_city = temp_country->cities + j;
                        if (strcmp(temp_city->name, city_name) == 0) {
                            printf("City %s found\n", city_name);
                            return;
                        }
                    }
                    fprintf(stderr, "ERROR: CITY NOT FOUND\n");
                    return;
                }
            }
            fprintf(stderr, "ERROR_ COUNTRY NOT FOUND\n");
            return;
        }
        temp = temp->next_client;
    }
    fprintf(stderr, "ERROR: CLIENT NOT FOUND\n");
}

void insert_city_name (Country *country, char *city_name) {

    if (country->cities == NULL) {
        country->cities = allocate_memory_trip_city();
        country->cities->name = allocate_memory_name(strlen(city_name));
        strcpy(country->cities->name, city_name);
        country->size_trip_cities = 1;
    }
    else {
        country->cities = reallocate_memory_cities(country, country->size_trip_cities);
        City *temp_city = country->cities + country->size_trip_cities;
        temp_city->name = 0;
        temp_city->name = allocate_memory_name(strlen(city_name));
        strcpy(temp_city->name, city_name);
        country->size_trip_cities += 1;
    }

}

//------------------POI-------------------------//
void insert_PoI (Client **head, uint32_t client_id, char *country_name, char *city_name, float x, float y) {

    if (is_list_empty(head)) {
        fprintf(stderr, "ERROR: NO CLIENTS AVAILABLE\n");
        return;
    }

    Client *temp_client = *head;

    while (temp_client != NULL) {
        if (temp_client->user_id == client_id) {
            Country *temp_country;
            for (int i = 0; i < temp_client->size_trips_to_be_made; ++i) {
                temp_country = temp_client->trips_to_be_made + i;
                if (strcmp(temp_country->name, country_name) == 0) {
                    City *temp_city;
                    for (int j = 0; j < temp_country->size_trip_cities; ++j) {
                        temp_city = temp_country->cities + j;
                        if (strcmp(temp_city->name, city_name) == 0) {
                            temp_city->coordinates = allocate_memory_points();
                            temp_city->coordinates->x = x;
                            temp_city->coordinates->y = y;
                            return;
                        }
                    }
                    fprintf(stderr, "ERROR: CITY NOT FOUND\n");
                    return;
                }
            }
            fprintf(stderr, "ERROR: COUNTRY NOT FOUND\n");
            return;
        }
        temp_client = temp_client->next_client;
    }
    fprintf(stderr, "ERROR: CLIENT NOT FOUND\n");
}

void remove_PoI (Client **head, uint32_t client_id, char *country_name, char *city_name) {
    if (is_list_empty(head)) {
        fprintf(stderr, "ERROR: NO CLIENTS AVAILABLE\n");
        return;
    }

    Client *temp_client = *head;

    while (temp_client != NULL) {
        if (temp_client->user_id == client_id) {
            Country *temp_country;
            for (int i = 0; i < temp_client->size_trips_to_be_made; ++i) {
                temp_country = temp_client->trips_to_be_made + i;
                if (strcmp(temp_country->name, country_name) == 0) {
                    City *temp_city;
                    for (int j = 0; j < temp_country->size_trip_cities; ++j) {
                        temp_city = temp_country->cities + j;
                        if (strcmp(temp_city->name, city_name) == 0) {
                            temp_city->coordinates = 0;
                            free (temp_city->coordinates);
                            return;
                        }
                    }
                    fprintf(stderr, "ERROR: CITY NOT FOUND\n");
                    return;
                }
            }
            fprintf(stderr, "ERROR: COUNTRY NOT FOUND\n");
            return;
        }
        temp_client = temp_client->next_client;
    }
    fprintf(stderr, "ERROR: CLIENT NOT FOUND\n");
}

void search_PoI (Client **head, uint32_t client_id, char *country_name, char *city_name) {
    if (is_list_empty(head)) {
        fprintf(stderr, "ERROR: NO CLIENTS AVAILABLE\n");
        return;
    }

    Client *temp_client = *head;

    while (temp_client != NULL) {

        if (temp_client->user_id == client_id) {
            Country *temp_country;
            for (int i = 0; i < temp_client->size_trips_to_be_made; ++i) {
                temp_country = temp_client->trips_to_be_made + i;
                if (strcmp(temp_country->name, country_name) == 0) {
                    City *temp_city;
                    for (int j = 0; j < temp_country->size_trip_cities; ++j) {
                        temp_city = temp_country->cities + j;
                        if (strcmp(temp_city->name, city_name) == 0) {
                            if (temp_city->coordinates == NULL) {
                                fprintf(stderr, "ERROR: PoI NOT FOUND\n");
                                return;
                            }
                            printf("City %s PoI:\nx: %.2f\ny: %.2f", city_name,
                                   temp_city->coordinates->x,
                                   temp_city->coordinates->y);
                            return;
                        }
                    }
                    fprintf(stderr, "ERROR: CITY NOT FOUND\n");
                    return;
                }
            }
            fprintf(stderr, "ERROR: COUNTRY NOT FOUND\n");
            return;
        }
        temp_client = temp_client->next_client;
    }
    fprintf(stderr, "ERROR: CLIENT NOT FOUND\n");
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

Country* allocate_memory_trip () {
    Country *new_country = calloc(1, sizeof(Country));
    if (new_country == NULL) fprintf(stderr, "NOT ABLE TO ALLOCATE MEMORY\n");
    return new_country;
}

char* allocate_memory_name (u_int64_t size) {
    char *names = calloc(size, sizeof(char));
    if (names == NULL) fprintf(stderr, "ERROR: NOT ABLE TO ALLOCATE MEMORY\n");
    return names;
}

City* allocate_memory_trip_city() {
    City *new_city = calloc (1, sizeof(City));
    if (new_city == NULL) fprintf(stderr, "ERROR_ NOT ABLE TO ALLOCATE MEMORY FOR CITY\n");
    return new_city;
}

Points* allocate_memory_points() {
    Points *brand_spanking_new_PoI = calloc (1, sizeof(Points));
    if (brand_spanking_new_PoI == NULL) fprintf(stderr, "ERROR: NOT ABLE TO ALLOCATE MEMORY FOR POINTS\n");
    return brand_spanking_new_PoI;
}

//------------------Reallocate-------------------------//

Country* realloc_memory_trip (Client *client, int size) {
    client->trips_to_be_made = realloc(client->trips_to_be_made, (size + 1) * sizeof(Country));
    if (client->trips_to_be_made == NULL) fprintf(stderr, "NOT ABLE TO REALLOCATE MEMORY\n");
    return client->trips_to_be_made;
}

char* realloc_memory_trip_name (char *trips, uint64_t size) {
    trips = realloc(trips, size);
    if (trips == 0) fprintf(stderr, "NOT ABLE TO REALLOCATE MEMORY\n");
    return trips;
}

City* reallocate_memory_cities(Country *country, int size) {
    country->cities = realloc(country->cities, (size + 1) * sizeof(City));
    if (country->cities == NULL) fprintf(stderr, "ERROR: NOT ABLE TO REALLOCATE MEMORY FOR CITY\n");
    return country->cities;
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


//------------------AUX-------------------------//
// TODO: ASK TEACHER
char* refactor_string_to_lower (char* str) {
   char temp;
    for (int i = 0; i < strlen(str) + 1; ++i) {
        if (isupper(*(str + i))) {
            temp = (char) tolower(*(str + i));
            *(str + i) = temp;
        }
    }
    return str;
}