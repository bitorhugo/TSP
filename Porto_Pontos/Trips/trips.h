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

void insert_city (COUNTRY *country, char *city_name, float coordinate_x, float coordinate_y);
void remove_city (COUNTRY *country, char *city_name);
void edit_city (COUNTRY *country, char *current_city_name, char* new_city_name, float new_x, float new_y);
CITY* search_city (COUNTRY *country, char *city_name);

#endif //TSP_TRIPS_H
