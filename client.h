//
// Created by Vitor Hugo on 31/10/2021.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

typedef struct Points{
    float x;
    float y;
}Points;

typedef struct Client{
  uint32_t user_id;
  char* address;
  uint16_t contact_number;
  uint32_t billing;
  Date registration;
  struct Client *next_client; // pointer for the next client
}Client;

typedef struct City{
    uint16_t city_id;
    Points coordinates;
}City; // Possible rename to gene

//-------------------------------------------//

Client *post_clients(FILE *file_clients);

/**
 * prints client
 * @param client
 */

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
 * prints all clients (linked list)
 * @param client start of linked list
 */
void print_clients(Client *client);

/**
 * reads from csv file all clients
 * @param head head of linked list
 */
void read_clients_from_file(Client *head);

//-------------------------------------------//

/**
 * Allocates memory for Client
 * @return pointer to newly allocated memory
 */
Client* allocate_memory_Client();

#endif //TSP_CLIENT_H
