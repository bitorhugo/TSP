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
}CLIENT;


CLIENT create_client (char *name, uint32_t VAT, char *address, uint32_t phone_number, int birth_day, int birth_month, int birth_year);
void insert_trip (CLIENT *client, char *country_name);
void remove_trip (CLIENT *client, char *country_name);
void edit_trip (CLIENT *client, char *current_country_name, char *new_country_name);
void print_trips (CLIENT *client, bool is_finished);
void print_finished_trip_specific (CLIENT *client, char *country_name, char *city_name, char *poi);

#endif //TSP_CLIENT_H
