//
// Created by Vitor Hugo on 31/10/2021.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef TSP_CLIENT_H
#define TSP_CLIENT_H

typedef struct {
    uint16_t day;
    uint16_t month;
    uint16_t year;
}sDate;

typedef struct {
    float x;
    float y;
}sPoints;

struct sClient{
  uint32_t user_id;
  char* address;
  uint16_t contact_number;
  uint32_t billing;
  sDate registration;
  struct sClient *next_in_line; // pointer for the next client
};

typedef struct {
    uint16_t city_id;
    sPoints coordinates;
}sCity; // Possible rename to gene



/**
 * creates new client
 * @param id id of client to be created
 * @return pointer to new client
 */
struct sClient *create_new_client(uint32_t id);

/**
 * prints client
 * @param client
 */
void print_client(struct sClient *client);


#endif //TSP_CLIENT_H
