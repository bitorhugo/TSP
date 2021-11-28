//
// Created by Vitor Hugo on 28/11/2021.
//

#include "client.h"

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

//------------------Allocate-------------------------//

City* allocate_memory_trip_city() {
    City *new_city = calloc (1, sizeof(City));
    if (new_city == NULL) fprintf(stderr, "ERROR_ NOT ABLE TO ALLOCATE MEMORY FOR CITY\n");
    return new_city;
}

//------------------Reallocate-------------------------//

City* reallocate_memory_cities(Country *country, int size) {
    country->cities = realloc(country->cities, (size + 1) * sizeof(City));
    if (country->cities == NULL) fprintf(stderr, "ERROR: NOT ABLE TO REALLOCATE MEMORY FOR CITY\n");
    return country->cities;
}