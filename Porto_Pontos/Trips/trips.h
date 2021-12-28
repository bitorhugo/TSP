//
// Created by Vitor Hugo on 27/12/2021.
//
#include "Cities/cities.h"

#ifndef TSP_TRIPS_H
#define TSP_TRIPS_H

typedef struct country {
    char *name;
    CITY *cities;
    int num_of_cities;
}COUNTRY;

COUNTRY *create_country (char *name);
void insert_city (COUNTRY *country, CITY *city);
void remove_city (COUNTRY *country, CITY *city);
void edit_city (COUNTRY *country, CITY *city, char* new_city_name, float new_x, float new_y);
CITY* search_city (COUNTRY *country, CITY *city);

#endif //TSP_TRIPS_H
