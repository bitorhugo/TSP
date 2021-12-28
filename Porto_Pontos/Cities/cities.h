//
// Created by Vitor Hugo on 27/12/2021.
//

#include "Points/points.h"
#include "Poi/poi.h"

#ifndef TSP_CITIES_H
#define TSP_CITIES_H

typedef struct city {
    char *name;
    POINTS coordinates;
    POI *poi;
    int num_of_poi;
}CITY;

CITY *create_city (char *city_name, float x, float y);
void insert_poi (CITY *city, char *poi);
void remove_poi (CITY *city, char *poi);
POI* search_poi (CITY *city, char *poi);

#endif //TSP_CITIES_H
