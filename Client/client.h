//
// Created by Vitor Hugo on 31/10/2021.
//

//------------------LIBRARIES-------------------------//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#include <unistd.h>
#include <math.h>

//------------------DEFINE-------------------------//

#ifndef TSP_CLIENT_H
#define TSP_CLIENT_H

#define FILE_LINE_SIZE 100

//------------------DATA-------------------------//

typedef struct date{
    uint16_t day;
    uint16_t month;
    uint16_t year;
}DATE;

typedef struct poi {
    char* name;
}POI;

typedef struct points {
    float x;
    float y;
} POINTS;

typedef struct city {
    char* name;
    POINTS * coordinates;
    POI *poi;
    int num_of_poi;
} CITY; // Possible rename to gene

typedef struct country {
    char* name;
    CITY* cities; // Possible rename to individual
    int size_trip_cities;
} COUNTRY; // Possible rename to population

typedef struct client {
  uint32_t user_id;
  //char* address;
  //uint16_t contact_number;
  //uint32_t billing;
  //Date registration;
  COUNTRY * trips_finished;
  int size_trips_finished;
  COUNTRY * trips_to_be_made;
  int size_trips_to_be_made;
  struct client *next_client; // pointer for the next client
} CLIENT;

typedef struct client_list {
    CLIENT client;
    int num_of_clients;
    struct client_list *next_client;
}CLIENT_LIST;

//------------------CLIENT-------------------------//

/**
 * inserts a new client
 * @param head head of linked list
 * @param at_head true if inserting at the beginning | false if at end
 * @param client_id clients id
 */
void insert_new_client (CLIENT **head, bool at_head, uint32_t client_id);

/**
 * insert new client at the head of linked list
 * @param head head of linked list
 */
void insert_new_client_head(CLIENT **head);

/**
 * inserts new client at tail
 * @param tail tail of linked list
 */
void insert_new_client_tail(CLIENT **head);

/**
 * Removes client by user id
 * @param head head of linked list
 */
void remove_client (CLIENT **head, uint32_t userid);

/**
 * searches client by his id
 * @param head head of linked list
 * @param userid wanted client
 */
CLIENT * search_client_by_id (CLIENT **head, uint32_t userid);

/**
 * sorts clients
 * @param head head of linked list
 * @param attribute 0 == ID | 1 == NAME
 */
void sort_clients (CLIENT **head, short attribute);

/**
 * sorts clients by id using selection sort: O(n^2)
 * @param head head of linked list
 */
void sort_clients_id (CLIENT **head);

/**
 * sorts clients by name
 * @param head head of linked list
 */
void sort_clients_name (CLIENT **head);

/**
 * prints clients
 * @param head head of linked list
 */
void print_clients(CLIENT **head);

/**
 * reads from csv file all clients
 * @param head head of linked list
 */
void read_clients_from_file(CLIENT **head);

//------------------TRIP-------------------------//

/**
 * adds trip to clients trips array
 * @param head head of linked list
 * @param client_id wanted client
 * @param country_name name of the country to insert
 */
void insert_trip (CLIENT *client, char* country_name);

/**
 * removes a trip from a client
 * @param head head of linked list
 * @param client_id wanted client
 * @param country_name name of the country to remove
 */
void remove_trip (CLIENT *client, char* country_name);

/**
 * edits trip of wanted client
 * @param head head of linked list
 * @param client_id wanted client
 * @param country_name trip to be replaced
 * @param new_country_name new trip
 */
void edit_trip (CLIENT *client, char* country_name, char* new_country_name);

/**
 * prints all trips wanted client made
 * @param head head of linked list
 * @param client_id wanted client
 */
void print_trips (CLIENT *client, bool is_finished);

/**
 * prints trips made with specific parameters
 * @param head head of linked list
 * @param client_id wanted client
 * @param country_name country name
 * @param city_name city name
 */
void print_trips_specific (CLIENT **head, uint32_t client_id, char *country_name, char *city_name, short is_finished);

/**
 * inserts country_name to client trips_to_be_made array
 * @param client wanted client
 * @param country_name country name
 */
void insert_trip_name(CLIENT *client, char *country_name);

/**
 * refactors countries' name to camel case (e.g. portugal -> Portugal || porTugal --> Portugal)
 * @param country_name country name
 * @param refactored_name refactored name
 */
void camel_case_name(char *country_name, char *refactored_name);

//------------------CITY-------------------------//

/**
 * inserts cities to visit
 * @param head head of linked list
 * @param client_id client wanted
 * @param country_name country name
 * @param city_name city to insert
 */
void insert_city (COUNTRY *country, char *city_name);

/**
 * removes a city from a trip
 * @param head head of linked list
 * @param client_id wanted client
 * @param country_name country name
 * @param city_name city to delete
 */
void remove_city (COUNTRY *country, char *city_name);

/**
 * edits a city from trip
 * @param head head of linked list
 * @param client_id wanted client
 * @param country_name country name
 * @param city_name city to be edited
 * @param new_city_name new city name
 */
void edit_city (COUNTRY *country, char *city_name, char *new_city_name);

/**
 * searches a city inside trip
 * @param head head of linked list
 * @param client_id wanted client
 * @param country_name country name
 * @param city_name city to print
 */
CITY * search_city (COUNTRY *country, char *city_name);

/**
 * inserts city_name to clients cities array
 * @param client wanted client
 * @param city_name city name
 */
void insert_city_name (COUNTRY *country, char *city_name);

//------------------CITY_COORDINATES-------------------------//

/**
 * insert Points of Interest of certain city
 * @param head head of linked list
 * @param client_id wanted client
 * @param country_name country name
 * @param city_name city name
 * @param x X coordinate
 * @param y Y coordinate
 */
void insert_coordinates (CITY *city, float x, float y);

/**
 * removes Points of Interest of certain city
 * @param head head of linked list
 * @param client_id wanted client
 * @param country_name country name
 * @param city_name city name
 */
void remove_coordinates (CITY *city);

void edit_coordinates (CITY *city, float new_x, float new_y);

/**
 * Searches Points of Interest of certain city
 * @param head head of linked list
 * @param client_id wanted client
 * @param country_name name of country
 * @param city_name name of city
 */
POINTS* search_coordinates (CITY *city);



//------------------CITY_PoI-------------------------//

void insert_PoI (CITY *city, char *poi_name);

void remove_PoI (CITY *city, char *poi_name);

POI* search_PoI (CITY *city, char *poi_name);

//------------------ALLOCATE-------------------------//

/**
 * Allocates memory for Client
 * @return pointer to newly allocated memory
 */
CLIENT * allocate_memory_Client();

/**
 * Allocates memory for clients trips
 * @return pointer to arrays first position
 */
COUNTRY * allocate_memory_trip();

/**
 * Allocates memory for names
 * @param size strlen of name
 * @return allocated char memory
 */
char* allocate_memory_name (uint64_t size);

/**
 * Allocates memory for city
 * @return pointer to newly allocated city
 */
CITY * allocate_memory_trip_city();

/**
 * Allocates memory for Points
 * @return pointer to newly allocated PoI
 */
POINTS * allocate_memory_points();

POI* allocate_memory_poi();

//------------------REALLOCATE-------------------------//

/**
 * Reallocates memory for client
 * @param trips data_structure to resize
 * @param size size to reallocate to
 * @return pointer to newly reallocated memory
 */
COUNTRY * realloc_memory_trip (CLIENT *client, int size);

/**
 *
 * @param trips trips
 * @param size size to reallocate to
 * @return pointer to arrays first position
 */
char* realloc_memory_trip_name (char *trip_name, uint64_t size);

/**
 * Reallocates memory for city name
 * @return pointer to newly reallocated memory
 */
CITY * reallocate_memory_cities(COUNTRY *country, int size);

POI* realloc_memory_poi (CITY *city, int size);

//------------------LINKED-LIST-------------------------//

/**
 * checks if linked list is empty
 * @param head head of list
 * @return 1 if true | 0 if false
 */
int is_list_empty (CLIENT **head);

/**
 * Frees memory used
 * Safely ends program
 * @param head head of liked list
 */
void free_clients_list (CLIENT **head);

//------------------FILES-------------------------//

/**
 * writes report to file
 * @param head head of linked list
 * @param client_id wanted client
 * @param is_binary true if type binary | false if type txt
 */
void write_report (CLIENT **head, uint32_t client_id, bool is_binary);

//------------------AUX-------------------------//
/**
 * Splits linked list into two halves
 * @param source
 * @param frontRef
 * @param backRef
 */
void FrontBackSplit(CLIENT * source, CLIENT ** frontRef, CLIENT ** backRef);

/**
 * Merges sorted lists
 * @param a
 * @param b
 * @return
 */
CLIENT *SortedMerge(CLIENT *a, CLIENT *b);

float float_rand( float min, float max );

int int_rand (int min, int max);

#endif //TSP_CLIENT_H
