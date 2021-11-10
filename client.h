//
// Created by Vitor Hugo on 31/10/2021.
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
    uint16_t city_id;
    Points coordinates;
} City; // Possible rename to gene

typedef struct Country {
    char* name;
    City *cities;
} Country;

typedef struct Client {
  uint32_t user_id;
  char* address;
  uint16_t contact_number;
  uint32_t billing;
  Date registration;
  Country* trips_finished;
  Country* trips_to_be_made;
  struct Client *next_client; // pointer for the next client
} Client;


//-------------------------------------------//

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

/**
 * adds trip to clients trips array
 * @param head head of linked list
 * @param client_id wanted client
 * @param country_name name of the country
 */
void create_trip_for_client (Client **head, uint32_t client_id, char* country_name);


//-------------------------------------------//

/**
 * Allocates memory for Client
 * @return pointer to newly allocated memory
 */
static Client* allocate_memory_Client();

/**
 * Allocates memory for clients trips
 * @return pointer to arrays first position
 */
Country* allocate_memory_trips();

/**
 * Allocates memory for trips names
 * @param size strlen of country name
 * @return allocated char memory
 */
static char* allocate_memory_trip_name (uint64_t size);

/**
 * checks if trips are null
 * @param trips pointer to trips of client
 */
bool check_trips_null (Country *trips);

/**
 * adds whitespaces after country name if necessary
 * @param country_name country name
 * @return refactored country name
 */
static char* add_whitespace_country_name(char* country_name);

/**
 * checks if linked list is empty
 * @param head head of list
 * @return 1 if true | 0 if false
 */
static int is_list_empty (Client **head);

/**
 * Frees memory used
 * Safely ends program
 * @param head head of liked list
 */
void free_clients_list (Client **head);

#endif //TSP_CLIENT_H
