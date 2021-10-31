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
}Date;

typedef struct {
    float x;
    float y;
}Points;

typedef struct {
  uint32_t user_id;
  char* address;
  uint16_t contact_number;
  uint32_t billing;
  Date registration;

  struct Client *next_client; // pointer for the next client
}Client;

typedef struct {
    uint16_t city_id;
    Points coordinates;

}City; // Possible rename to gene







#endif //TSP_CLIENT_H
