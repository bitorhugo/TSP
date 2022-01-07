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

/**
 * inserts a city into country
 * @param country country
 * @param city_name city name to insert
 * @param coordinate_x coordinate x
 * @param coordinate_y coordinate y
 */
void insert_city (COUNTRY *country, char *city_name, float coordinate_x, float coordinate_y);
/**
 * removes a city from country
 * @param country country
 * @param city_name city name to remove
 */
void remove_city (COUNTRY *country, char *city_name);
/**
 * edits a city name and coordinates from country
 * @param country country
 * @param current_city_name current city name
 * @param new_city_name new city name
 * @param new_x new coordinate x
 * @param new_y new coordinate y
 */
void edit_city (COUNTRY *country, char *current_city_name, char* new_city_name, float new_x, float new_y);
/**
 * searches for a city from country
 * @param country country
 * @param city_name city name
 * @return address of city
 */
CITY* search_city (COUNTRY *country, char *city_name);

#endif //TSP_TRIPS_H
