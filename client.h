//
// Created by Vitor Hugo on 31/10/2021.
//  Estudo AG: Elitismo, cruzamento (cycle crossover), ...
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

//-------------------------------------------//

#ifndef TSP_CLIENT_H
#define TSP_CLIENT_H

#define FILE_LINE_SIZE 100

//-------------------------------------------//

typedef struct Date{
    uint16_t day;
    uint16_t month;
    uint16_t year;
}Date;

typedef struct Points {
    float x;
    float y;
} Points;

typedef struct City {
    uint32_t city_id;
    Points coordinates;
} City; // Possible rename to gene

typedef struct Country {
    char* name;
    City *cities; // Possible rename to individual
} Country; // Possible rename to population

typedef struct Client {
  uint32_t user_id;
  char* address;
  uint16_t contact_number;
  uint32_t billing;
  Date registration;
  Country* trips_finished;
  Country* trips_to_be_made;
  int size_trips_to_be_made;
  struct Client *next_client; // pointer for the next client
} Client;

//-------------------------------------------//

/**
 * insert new client
 * @param head head of linked list
 * @param position 0 -> head | 1 -> tail
 */
void insert_new_client (Client **head, bool position, uint32_t *client_id);

/**
 * insert new client at the head of linked list
 * @param head head of linked list
 */
void insert_new_client_head(Client **head);

/**
 * inserts new client at tail
 * @param tail tail of linked list
 */
void insert_new_client_tail(Client **head);

/**
 * Removes client by user id
 * @param head head of linked list
 */
void remove_client (Client **head, uint32_t userid);

void search_client_by_id (Client **head, uint32_t userid);

void print_clients(Client **head);

/**
 * reads from csv file all clients
 * @param head head of linked list
 */
void read_clients_from_file(Client **head);

/**
 * Sorts list by VAT
 * @param head head of linked list
 */
void sort_clients_VAT(Client **head);

//------------------TRIPS-------------------------//

/**
 * adds trip to clients trips array
 * @param head head of linked list
 * @param client_id wanted client
 * @param country_name name of the country to insert
 */
void insert_trip_for_client (Client **head, uint32_t client_id, char* country_name);

/**
 * removes a trip from a client
 * @param head head of linked list
 * @param client_id wanted client
 * @param country_name name of the country to remove
 */
void remove_trip_for_client (Client **head, uint32_t client_id, char* country_name);

/**
 * edits trip of wanted client
 * @param head head of linked list
 * @param client_id wanted client
 * @param country_name trip to be replaced
 * @param new_country_name new trip
 */
void edit_trip_for_client (Client **head, uint32_t client_id, char* country_name, char* new_country_name);

/**
 * prints all trips wanted client made
 * @param head head of linked list
 * @param client_id wanted client
 */
void print_trips (Client **head, uint32_t client_id);

//------------------TRIPS-------------------------//

/**
 * inserts cities to visit
 * @param head head of linked list
 * @param client_id client wanted
 * @param country_name country name
 * @param city_name city to insert
 */
void insert_trip_city (Client **head, uint32_t client_id, char *country_name, char *city_name);

/**
 * deletes a city from trip
 * @param head head of linked list
 * @param client_id wanted client
 * @param country_name country name
 * @param city_name city to delete
 */
void delete_trip_city (Client **head, uint32_t client_id, char *country_name, char *city_name);

/**
 * edits a city from trip
 * @param head head of linked list
 * @param client_id wanted client
 * @param country_name country name
 * @param city_name city to be edited
 * @param new_city_name new city name
 */
void edit_trip_city (Client **head, uint32_t client_id, char *country_name, char *city_name, char *new_city_name);

/**
 * searches a city inside trip
 * @param head head of linked list
 * @param client_id wanted client
 * @param country_name country name
 * @param city_name city to print
 */
void search_trip_city (Client **head, uint32_t client_id, char *country_name, char *city_name);


//-------------------------------------------//

/**
 * Allocates memory for Client
 * @return pointer to newly allocated memory
 */
Client* allocate_memory_Client();

/**
 * Reallocates memory for client
 * @param trips data_structure to resize
 * @param size size to reallocate to
 * @return pointer to newly reallocated memory
 */
static Country* realloc_memory_trip (Client *client, int size);

/**
 * allocates trip and puts country
 * @param client client
 * @param country country to add
 * @param is_empty 1 if empty | 0 if not first trip
 */
char* insert_trip_name_client (Country* client, char* country);

/**
 * Allocates memory for clients trips
 * @return pointer to arrays first position
 */
static Country* allocate_memory_trip();

/**
 * Allocates memory for trips names
 * @param size strlen of country name
 * @return allocated char memory
 */
char* allocate_memory_trip_name (uint64_t size);

/**
 *
 * @param trips trips
 * @param size size to reallocate to
 * @return pointer to arrays first position
 */
char* realloc_memory_trip_name (char *trip_name, uint64_t size);

/**
 * checks if linked list is empty
 * @param head head of list
 * @return 1 if true | 0 if false
 */
int is_list_empty (Client **head);

/**
 * Frees memory used
 * Safely ends program
 * @param head head of liked list
 */
void free_clients_list (Client **head);

#endif //TSP_CLIENT_H
