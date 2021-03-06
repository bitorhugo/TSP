//
// Created by Vitor Hugo on 27/12/2021.
//

#include "trips.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

CITY* allocate_memory_city();
CITY* reallocate_memory_city (COUNTRY *country);
void set_city_name (CITY *city, char *city_name, bool is_alloc);

void insert_city (COUNTRY *country, char *city_name, float coordinate_x, float coordinate_y) {
    CITY new_city = {0};
    set_city_name(&new_city, city_name, true);
    new_city.coordinates.x = coordinate_x;
    new_city.coordinates.y = coordinate_y;

    if (country->num_of_cities < 1) {
        country->cities = allocate_memory_city();
        *country->cities = new_city;
        country->num_of_cities += 1;
    }
    else {
        country->cities = reallocate_memory_city(country);
        CITY *temp_city = country->cities + country->num_of_cities;
        temp_city->name = 0, temp_city->coordinates.x = 0, temp_city->coordinates.y = 0, temp_city->poi = 0, temp_city->num_of_poi = 0;
        *temp_city = new_city;
        country->num_of_cities += 1;
    }
}

void remove_city (COUNTRY *country, char *city_name) {
    for (size_t i = 0; i < country->num_of_cities; ++i) {
        CITY *temp_city = country->cities + i;
        if (strcmp(temp_city->name, city_name) == 0) {
            for (size_t j = i; j < country->num_of_cities; ++j) {
                *(country->cities + j) = *(country->cities + j + 1);
            }
            country->num_of_cities -= 1;
            country->cities = reallocate_memory_city(country);
            return;
        }
    }
    fprintf(stderr, "ERROR: CITY NOT FOUND\n");
}

void edit_city (COUNTRY *country, char *current_city_name, char* new_city_name, float new_x, float new_y) {

    CITY *temp_city = search_city(country, current_city_name);
    if (temp_city == NULL) {
        fprintf(stderr, "ERROR: CITY NOT FOUND\n");
        return;
    }
    set_city_name(temp_city, new_city_name, false);
    temp_city->coordinates.x = new_x;
    temp_city->coordinates.y = new_y;
}

CITY* search_city (COUNTRY *country, char *city_name) {
    if (country->num_of_cities < 1) {
        fprintf(stderr, "ERROR: NO CITIES AVAILABLE\n");
        return NULL;
    }
    for (size_t i = 0; i < country->num_of_cities; ++i) {
        CITY *temp_city = country->cities + i;
        if (strcmp(temp_city->name, city_name) == 0) {
            return temp_city;
        }
    }
    return NULL;
}

CITY* allocate_memory_city () {
    CITY *new_city = calloc(1, sizeof(CITY));
    return new_city;
}

CITY* reallocate_memory_city (COUNTRY *country) {
    country->cities = realloc(country->cities, (country->num_of_cities + 1) * sizeof(CITY));
    if (country->cities == NULL) {
        fprintf(stderr, "ERROR: NOT ABLE TO REALLOCATE CITY\n");
    }
    return country->cities;
}

void set_city_name (CITY *city, char *city_name, bool is_alloc) {
    if (is_alloc) {
        city->name = allocate_memory_str(strlen(city_name));
        strcpy(city->name, city_name);
    }
    else {
        city->name = reallocate_memory_str(city->name, strlen(city_name));
        strcpy(city->name, city_name);
    }
}