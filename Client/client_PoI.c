//
// Created by Vitor Hugo on 28/11/2021.
//
#include "client.h"

void insert_PoI (CITY *city, char *poi_name) {
    if (city == NULL) {
        fprintf(stderr, "ERROR: NOT ABLE TO FIND CITY\n");
        return;
    }

    if (city->poi == NULL) {
        city->poi = allocate_memory_poi();
        city->poi->name = allocate_memory_name(strlen(poi_name));
        strcpy(city->poi->name, poi_name);
        city->num_of_poi = 1;
    }
    else {
        city->poi = realloc_memory_poi (city, city->num_of_poi);
        POI *temp_poi = city->poi + city->num_of_poi;
        temp_poi->name = 0;
        temp_poi->name = allocate_memory_name(strlen(poi_name));
        strcpy(temp_poi->name, poi_name);
        city->num_of_poi += 1;
    }

}

void remove_PoI (CITY *city, char *poi_name) {
    if (city == NULL) {
        fprintf(stderr, "ERROR: NOT ABLE TO FIND CITY\n");
        return;
    }

    POI *temp_poi;
    for (int i = 0; i < city->num_of_poi; ++i) {
        temp_poi = city->poi + i;
        if (strcmp(temp_poi->name, poi_name) == 0) {
            for (int j = 0; j < city->num_of_poi - i; ++j) {
                *(temp_poi + j) = *(temp_poi + j + 1);
            }
            city->num_of_poi -= 1;
            realloc_memory_poi(city, city->num_of_poi);
            printf("PoI %s removed\n", poi_name);
            return;
        }
    }

    fprintf(stderr, "ERROR: POI NOT FOUND\n");

}

POI* search_PoI (CITY *city, char *poi_name) {

    if (city == NULL) {
        fprintf(stderr, "ERROR: NOT ABLE TO FIND CITY\n");
        return NULL;
    }

    POI* temp_poi;
    for (int i = 0; i < city->num_of_poi; ++i) {
        temp_poi = city->poi + i;
        if (strcmp(temp_poi->name, poi_name) == 0) {
            printf("PoI found: %s\n", poi_name);
            return temp_poi;
        }
    }
    fprintf(stderr, "ERROR: POI NOT FOUND\n");
    return NULL;

}

//------------------Allocate-------------------------//

POI* allocate_memory_poi() {
    POI *new_poi = calloc(1, sizeof (POI));
    if (new_poi == NULL) fprintf(stderr, "ERROR: NOT ABLE TO ALLOCATE MEMORY FOR POI\n");
    return new_poi;
}

//------------------Reallocate-------------------------//

POI* realloc_memory_poi (CITY *city, int size) {
    POI *new_poi = realloc(city->poi, (size + 1) * sizeof(POI));
    if (new_poi == NULL) fprintf(stderr, "ERROR: NOT ABLE TO REALLOCATE MEMORY FOR POI\n");
    return new_poi;
}