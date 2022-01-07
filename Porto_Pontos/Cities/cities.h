//
// Created by Vitor Hugo on 27/12/2021.
//

#include "Points/points.h"
#include "Poi/poi.h"

#ifndef TSP_CITIES_H
#define TSP_CITIES_H

typedef struct city {
    char *name;
    char *description;
    POINTS coordinates;
    POI *poi;
    int num_of_poi;
}CITY;

/**
 * inserts a poi into city
 * @param city city
 * @param poi point of interest
 */
void insert_poi (CITY *city, char *poi);
/**
 * removes poi from city
 * @param city city
 * @param poi point of interest
 */
void remove_poi (CITY *city, char *poi);
/**
 * searches for a poi from city
 * @param city city
 * @param poi point of interest
 * @return address of poi
 */
POI* search_poi (CITY *city, char *poi);
/**
 * inserts a description of the city
 * @param city city
 * @param description description
 */
void insert_description (CITY *city, char *description);
/**
 * edits a description of a city
 * @param city city
 * @param new_description new description
 */
void edit_description (CITY *city, char *new_description);

#endif //TSP_CITIES_H
