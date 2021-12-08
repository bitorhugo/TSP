//
// Created by Vitor Hugo on 28/11/2021.
//

#include "client.h"

//------------------Cities-------------------------//

void insert_city (COUNTRY *country, char *city_name) {

    insert_city_name(country, city_name); // Pass Country due to City not being allocated yet

}

void remove_city (COUNTRY *country, char *city_name) {

    CITY *temp_city;
    for (int i = 0; i < country->size_trip_cities; ++i) {
        temp_city = country->cities + i;
        if (strcmp(temp_city->name, city_name) == 0) {
            for (int j = 0; j < country->size_trip_cities - i; ++j) {
                *(temp_city + j) = *(temp_city + j + 1);
            }
            country->size_trip_cities -= 1;
            reallocate_memory_cities(country, country->size_trip_cities);
            printf("City %s removed\n", city_name);
            return;
        }
    }

}

void edit_city (COUNTRY *country, char *city_name, char *new_city_name) {

    CITY *temp_city = search_city(country, city_name);

    if (temp_city != NULL) {
        realloc_memory_trip_name(temp_city->name, strlen(new_city_name));
        strcpy(temp_city->name, new_city_name);
        return;
    }


}

CITY * search_city (COUNTRY *country, char *city_name) {

    CITY *temp_city;
    for (int i = 0; i < country->size_trip_cities; ++i) {
        temp_city = country->cities + i;
        if (strcmp(temp_city->name, city_name) == 0) {
            printf("City %s found\n", city_name);
            return temp_city;
        }
    }
    fprintf(stderr, "ERROR: CITY NOT FOUND\n");
    return NULL;

}

void insert_city_name (COUNTRY *country, char *city_name) {

    if (country->cities == NULL) {
        country->cities = allocate_memory_trip_city();
        country->cities->name = allocate_memory_name(strlen(city_name));
        strcpy(country->cities->name, city_name);
        country->size_trip_cities = 1;
    }
    else {
        country->cities = reallocate_memory_cities(country, country->size_trip_cities);
        CITY *temp_city = country->cities + country->size_trip_cities;
        temp_city->name = 0;
        temp_city->name = allocate_memory_name(strlen(city_name));
        strcpy(temp_city->name, city_name);
        country->size_trip_cities += 1;
    }

}

//------------------Coordinates-------------------------//

void insert_coordinates (CITY *city, float x, float y) {

    if (city == NULL) {
        fprintf(stderr, "ERROR: CITY NOT FOUND\n");
        return;
    }
    city->coordinates = allocate_memory_points();
    city->coordinates->x = x;
    city->coordinates->y = y;

}

void remove_coordinates (CITY *city) {

    if (city == NULL) {
        fprintf(stderr, "ERROR: CITY NOT FOUND\n");
        return;
    }
    city->coordinates = NULL;
    free (city->coordinates);

}

void edit_coordinates (CITY *city, float new_x, float new_y) {

    if (city == NULL) {
        fprintf(stderr, "ERROR: CITY NOT FOUND\n");
        return;
    }

    POINTS *temp_points = search_coordinates(city);

    temp_points->x = new_x;
    temp_points->y = new_y;

}

POINTS* search_coordinates (CITY *city) {

    if (city == NULL || city->coordinates == NULL) {
        fprintf(stderr, "ERROR: NOT ABLE TO SEARCH PoI\n");
        return NULL;
    }
    printf("City %s\nx = %.2f, y = %.2f\n", city->name, city->coordinates->x, city->coordinates->y);
    return city->coordinates;

}

//------------------Allocate-------------------------//

CITY * allocate_memory_trip_city() {
    CITY *new_city = calloc (1, sizeof(CITY));
    if (new_city == NULL) fprintf(stderr, "ERROR: NOT ABLE TO ALLOCATE MEMORY FOR CITY\n");
    return new_city;
}

POINTS * allocate_memory_points() {
    POINTS *brand_spanking_new_PoI = calloc (1, sizeof(POINTS));
    if (brand_spanking_new_PoI == NULL) fprintf(stderr, "ERROR: NOT ABLE TO ALLOCATE MEMORY FOR POINTS\n");
    return brand_spanking_new_PoI;
}

//------------------Reallocate-------------------------//

CITY * reallocate_memory_cities(COUNTRY *country, int size) {
    country->cities = realloc(country->cities, (size + 1) * sizeof(CITY));
    if (country->cities == NULL) fprintf(stderr, "ERROR: NOT ABLE TO REALLOCATE MEMORY FOR CITY\n");
    return country->cities;
}