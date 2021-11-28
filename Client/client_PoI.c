//
// Created by Vitor Hugo on 28/11/2021.
//
#include "client.h"

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
                            printf("City %s PoI:\nx: %.2f\ny: %.2f\n", city_name,
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

Points* allocate_memory_points() {
    Points *brand_spanking_new_PoI = calloc (1, sizeof(Points));
    if (brand_spanking_new_PoI == NULL) fprintf(stderr, "ERROR: NOT ABLE TO ALLOCATE MEMORY FOR POINTS\n");
    return brand_spanking_new_PoI;
}

//------------------Reallocate-------------------------//

