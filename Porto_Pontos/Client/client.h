//
// Created by Vitor Hugo on 27/12/2021.
//
#include "Trips/trips.h"
#include "Date/date.h"

#include <stdlib.h>
#include <stdbool.h>

#ifndef TSP_CLIENT_H
#define TSP_CLIENT_H

typedef struct client {
    uint32_t VAT;
    char *name;
    char *address;
    uint32_t phone_number;
    DATE birth;
    DATE registration;
    COUNTRY *booked_trips;
    int size_booked_trips;
    COUNTRY *finished_trips;
    int size_finished_trips;
} CLIENT;

/**
 * books a trip for a client
 * @param client client
 * @param country_name country name to insert
 */
void book_trip(CLIENT *client, char *country_name);

/**
 * removes a booked trip from a client
 * @param client client client
 * @param country_name country name to remove
 */
void remove_trip(CLIENT *client, char *country_name);

/**
 * edits a booked trip from a client
 * @param client client
 * @param current_country_name current countries name
 * @param new_country_name new countries name
 */
void edit_trip(CLIENT *client, char *current_country_name, char *new_country_name);

COUNTRY* search_trip (CLIENT *client, char *country_name, bool is_finished);
/**
 * prints trips from a client
 * @param client client
 * @param is_finished 0: print booked trips || 1: print finished trips
 */
void print_trips(CLIENT *client, bool is_finished);

/**
 * finishes a trip for a client from his booked trips
 * @param client client
 * @param booked_trip client booked trips
 */
void finish_trip(CLIENT *client, COUNTRY *booked_trip);

/**
* prints finished trips with specific content
* @param client client
* @param country_name country name
* @param city_name city name
* @param poi point of interest name
*/
void print_finished_trip_specific(CLIENT *client, char *country_name, char *city_name, char *poi);

#endif //TSP_CLIENT_H
