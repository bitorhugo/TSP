//
// Created by Vitor Hugo on 28/11/2021.
//
#include "client.h"

//------------------TRIPS-------------------------//

void insert_trip (Client **head, uint32_t client_id, char* country_name) {

    if (is_list_empty(head)) {
        fprintf(stderr, "ERROR: NO CLIENTS AVAILABLE\n");
        return;
    }

    char refactored_name[strlen(country_name) + 1]; // country_name is static so it can't be modified
    camel_case_name(country_name, refactored_name);

    Client *temp = *head; // temp for going through linked list
    while (temp != NULL) {
        if (temp->user_id == client_id) { // searches for wanted client

            insert_trip_name(temp, refactored_name);
            return;
        }
        temp = temp->next_client;
    }
    printf("Client not found\n");
}

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

void print_trips (Client **head, uint32_t client_id, short is_finished) {

    if (is_list_empty(head)) {
        fprintf(stderr, "ERROR: NO CLIENTS AVAILABLE\n");
        return;
    }

    Client *temp = *head;

    while (temp != NULL) {
        if (temp->user_id == client_id) {
            if (is_finished == 0) {
                if (temp->size_trips_to_be_made == 0) fprintf(stderr, "NO TRIPS FOUND\n");
                for (int i = 0; i < temp->size_trips_to_be_made; ++i) {
                    Country *temp_country = temp->trips_to_be_made + i;
                    printf("%s ", temp_country->name);
                }
                printf("\n");
                return;
            }
            else {
                if (temp->size_trips_finished == 0) fprintf(stderr, "ERROR: NO TRIPS FOUND\n");
                for (int i = 0; i < temp->size_trips_finished; ++i) {
                    Country *temp_country = temp->trips_finished + i;
                    printf("%s - ", temp_country->name);
                }
                printf("\n");
                return;
            }
        }
        temp = temp->next_client;
    }
    fprintf(stderr, "CLIENT NOT FOUND\n");
}

void print_trips_specific (Client **head, uint32_t client_id, char *country_name, char *city_name, short is_finished) {
    if (is_list_empty(head)) {
        fprintf(stderr, "ERROR: NO CLIENTS AVAILABLE\n");
        return;
    }
    Client *temp_client = *head;
    while (temp_client != NULL) {
        if (temp_client->user_id == client_id) {
            if (is_finished == 1) {
                Country *temp_country;
                for (int i = 0; i < temp_client->size_trips_finished; ++i) {
                    temp_country = temp_client->trips_finished + i;
                    if (strcmp(temp_country->name, country_name) == 0) {
                        City *temp_city;
                        for (int j = 0; j < temp_country->size_trip_cities; ++j) {
                            temp_city = temp_country->cities + j;
                            if (strcmp(temp_city->name, city_name) == 0) {
                                if (temp_city->coordinates == 0) {
                                    fprintf(stderr, "ERROR: PoI NOT FOUND\n");
                                    return;
                                }
                                printf("Trips finished:\nCity %s\nPoI: x = %.2f, y = %.2f\n",
                                       city_name, temp_city->coordinates->x, temp_city->coordinates->y);
                            }
                        }
                        fprintf(stderr, "ERROR: CITY NOT FOUND\n");
                        return;
                    }
                }
                fprintf(stderr, "ERROR: TRIP NOT FOUND\n");
                return;
            }
            else {
                Country *temp_country;
                for (int i = 0; i < temp_client->size_trips_to_be_made; ++i) {
                    temp_country = temp_client->trips_to_be_made + i;
                    if (strcmp(temp_country->name, country_name) == 0) {
                        City *temp_city;
                        for (int j = 0; j < temp_country->size_trip_cities; ++j) {
                            temp_city = temp_country->cities + j;
                            if (strcmp(temp_city->name, city_name) == 0) {
                                if (temp_city->coordinates == 0) {
                                    fprintf(stderr, "ERROR: PoI NOT FOUND\n");
                                    return;
                                }
                                printf("Trips finished:\nCity %s\nPoI: x = %.2f, y = %.2f\n",
                                       city_name, temp_city->coordinates->x, temp_city->coordinates->y);
                                return;
                            }
                        }
                        fprintf(stderr, "ERROR: CITY NOT FOUND\n");
                        return;
                    }
                }
                fprintf(stderr, "ERROR: TRIP NOT FOUND\n");
                return;
            }
        }
        temp_client = temp_client->next_client;
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

//------------------Allocate-------------------------//

Country* allocate_memory_trip () {
    Country *new_country = calloc(1, sizeof(Country));
    if (new_country == NULL) fprintf(stderr, "NOT ABLE TO ALLOCATE MEMORY\n");
    return new_country;
}

//------------------Reallocate-------------------------//

Country* realloc_memory_trip (Client *client, int size) {
    client->trips_to_be_made = realloc(client->trips_to_be_made, (size + 1) * sizeof(Country));
    if (client->trips_to_be_made == NULL) fprintf(stderr, "NOT ABLE TO REALLOCATE MEMORY\n");
    return client->trips_to_be_made;
}

void camel_case_name(char *country_name, char *refactored_name) {
    for (int i = 0; i < strlen(country_name) + 1; ++i) {
        refactored_name[i] = (char) tolower(country_name[i]);
    }
    refactored_name[0] = (char) toupper(refactored_name[0]);
}

