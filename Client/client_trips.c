//
// Created by Vitor Hugo on 28/11/2021.
//
#include "client.h"

//------------------TRIPS-------------------------//

void insert_trip (CLIENT *client, char* country_name) {

    char refactored_name[strlen(country_name) + 1]; // country_name is static so it can't be modified
    camel_case_name(country_name, refactored_name);

    insert_trip_name(client, refactored_name);

}

void remove_trip (CLIENT *client, char* country_name) {

    for (int i = 0; i < client->size_trips_to_be_made; ++i) {
        COUNTRY *temp3 = client->trips_to_be_made + i;
        if (strcmp(temp3->name, country_name) == 0) {
            for (int j = i; j < client->size_trips_to_be_made; ++j) {
                *(client->trips_to_be_made + j) = *(client->trips_to_be_made + j + 1);
            }
            client->size_trips_to_be_made -= 1;
            realloc_memory_trip(client, client->size_trips_to_be_made);
            return;
        }
    }
    fprintf(stderr, "TRIP NOT FOUND\n");
}

void edit_trip (CLIENT *client, char* country_name, char* new_country_name) {

    for (int i = 0; i < client->size_trips_to_be_made; ++i) {
        COUNTRY *temp_country = client->trips_to_be_made + i;
        if (strcmp(temp_country->name, country_name) == 0) {
            realloc_memory_trip_name(temp_country->name, strlen(new_country_name));
            strcpy(temp_country->name, new_country_name);
            return;
        }
    }

}

COUNTRY* search_trip_finished (CLIENT* client, char* country_name) {
    if (client->size_trips_finished == 0) {
        fprintf(stderr, "ERROR: NO FINISHED TRIPS FOUND\n");
        return NULL;
    }
    COUNTRY* temp_country;
    for (size_t i = 0; i < client->size_trips_finished; ++i) {
        temp_country = client->trips_finished + i;
        if (strcmp(temp_country->name, country_name) == 0) {
            return temp_country;
        }
    }
    fprintf(stderr, "ERROR: FINISHED TRIP NOT FOUND\n");
    return NULL;
}

void print_trips (CLIENT *client, bool is_finished) {
    if (is_finished) {
        if (client->size_trips_finished == 0){
            fprintf(stderr, "NO TRIPS FOUND\n");
            return;
        }
        for (int i = 0; i < client->size_trips_finished; ++i) {
            COUNTRY *temp_country = client->trips_finished + i;
            printf("%s - ", temp_country->name);
        }
        printf("\n");
        return;
    }
    else {
        if (client->size_trips_to_be_made == 0){
            fprintf(stderr, "NO TRIPS FOUND\n");
            return;
        }
        for (int i = 0; i < client->size_trips_to_be_made; ++i) {
            COUNTRY *temp_country = client->trips_to_be_made + i;
            printf("%s ", temp_country->name);
        }
        printf("\n");
        return;
    }
}

COUNTRY* print_finished_trips_specific (CLIENT *client, char *country_name, char *city_name, char *PoI) {
    if (client->size_trips_finished == 0) {
        fprintf(stderr, "ERROR: NO TRIPS FINISHED\n");
        return NULL;
    }

    COUNTRY *temp_country = search_trip_finished(client, country_name);
    CITY *temp_city = search_city(temp_country, city_name);
    POI *temp_PoI = search_PoI(temp_city, PoI);
    return temp_country;

}

void insert_trip_name(CLIENT *client, char *country_name) {
    if (client->trips_to_be_made == NULL) {
        client->trips_to_be_made = allocate_memory_trip();
        client->trips_to_be_made->name = allocate_memory_name(strlen(country_name));
        strcpy(client->trips_to_be_made->name, country_name);
        client->size_trips_to_be_made = 1;
    }
    else {
        client->trips_to_be_made = realloc_memory_trip(client, client->size_trips_to_be_made);
        COUNTRY *temp_country = client->trips_to_be_made + client->size_trips_to_be_made;
        temp_country->name = 0, temp_country->cities = 0, temp_country->size_trip_cities = 0;
        temp_country->name = allocate_memory_name(strlen(country_name));
        strcpy(temp_country->name, country_name);
        client->size_trips_to_be_made += 1;
    }
}

void camel_case_name(char *country_name, char *refactored_name) {
    for (int i = 0; i < strlen(country_name) + 1; ++i) {
        refactored_name[i] = (char) tolower(country_name[i]);
    }
    refactored_name[0] = (char) toupper(refactored_name[0]);
}

//------------------Allocate-------------------------//

COUNTRY * allocate_memory_trip () {
    COUNTRY *new_country = calloc(1, sizeof(COUNTRY));
    if (new_country == NULL) fprintf(stderr, "NOT ABLE TO ALLOCATE MEMORY\n");
    return new_country;
}

//------------------Reallocate-------------------------//

COUNTRY * realloc_memory_trip (CLIENT *client, int size) {
    client->trips_to_be_made = realloc(client->trips_to_be_made, (size + 1) * sizeof(COUNTRY));
    if (client->trips_to_be_made == NULL) fprintf(stderr, "NOT ABLE TO REALLOCATE MEMORY\n");
    return client->trips_to_be_made;
}


