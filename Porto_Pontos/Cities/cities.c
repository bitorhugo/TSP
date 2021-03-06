//
// Created by Vitor Hugo on 27/12/2021.
//

#include "cities.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


POI* allocate_memory_poi ();
POI* reallocate_memory_poi (CITY *city, int size);

void insert_poi (CITY *city, char *poi) {
    if (city->num_of_poi < 1) {
        city->poi = allocate_memory_poi();
        city->poi->name = allocate_memory_str(strlen(poi));
        strcpy(city->poi->name, poi);
        city->num_of_poi = 1;
    }
    else {
        city->poi = reallocate_memory_poi(city, city->num_of_poi + 1);
        POI *temp_poi = city->poi + city->num_of_poi;
        temp_poi->name = allocate_memory_str(strlen(poi));
        strcpy(temp_poi->name, poi);
        city->num_of_poi += 1;
    }
}
void remove_poi (CITY *city, char *poi) {
    if (city->num_of_poi < 1) {
        fprintf(stderr, "ERROR: NO POI AVAILABLE\n");
        return;
    }
    for (size_t i = 0; i < city->num_of_poi; ++i) {
        POI *temp_poi = city->poi + i;
        if (strcmp(temp_poi->name, poi) == 0) {
            for (size_t j = 0; j < city->num_of_poi - i; j++) {
                temp_poi = temp_poi + j;
                *(temp_poi) = *(temp_poi + 1);
            }
            city->num_of_poi -= 1;
            reallocate_memory_poi(city, city->num_of_poi);
            return;
        }
    }
    fprintf(stderr, "ERROR: POI NOT FOUND\n");
}
POI* search_poi (CITY *city, char *poi) {
    if (city->num_of_poi < 1) {
        fprintf(stderr, "ERROR: NO POI AVAILABLE\n");
        return NULL;
    }
    for (size_t i = 0; i < city->num_of_poi; ++i) {
        POI *temp_poi = city->poi + i;
        if (strcmp(temp_poi->name, poi) == 0) {
            return temp_poi;
        }
    }
    fprintf(stderr, "ERROR: POI NOT FOUND\n");
    return NULL;
}

void insert_description (CITY *city, char *description) {
    if (city->description != NULL) {
        fprintf(stderr, "ERROR: CITY ALREADY HAS A DESCRIPTION\n");
        return;
    }
    else {
        city->description = allocate_memory_str(strlen(description));
        strcpy(city->description, description);
    }
}
void edit_description (CITY *city, char *new_description) {
    if (city->description == NULL) {
        fprintf(stderr, "ERROR: CITY DOES NOT HAVE A DESCRIPTION\n");
        return;
    }
    else {
        city->description = reallocate_memory_str(city->description, strlen(new_description));
        strcpy(city->description, new_description);
    }
}

POI* allocate_memory_poi () {
    POI *new_poi = calloc(1, sizeof(POI));
    if (new_poi == NULL) {
        fprintf(stderr, "ERROR: NOT ABLE TO ALLOCATE POI\n");
    }
    return new_poi;
}

POI* reallocate_memory_poi (CITY *city, int size) {
    city->poi = realloc(city->poi, (size) * sizeof(POI));
    if (city->poi == NULL) {
        fprintf (stderr, "ERROR: NOT ABLE TO REALLOCATE POI\n");
    }
    return city->poi;
}

char* allocate_memory_str (uint64_t size) {
    char *str = calloc(size, sizeof (char));
    if (str == NULL) {
        fprintf(stderr, "ERROR: NOT ABLE TO ALLOCATE STRING\n");
    }
    return str;
}

char* reallocate_memory_str (char *str, uint64_t size) {
    str = realloc(str, size * sizeof(char));
    if (str == NULL) {
        fprintf(stderr, "ERROR: NOT ABLE TO REALLOCATE MEMORY FOR NAME\n");
    }
    return str;
}