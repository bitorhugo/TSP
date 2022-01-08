//
// Created by Vitor Hugo on 08/01/2022.
//

#include "test_poi.h"


int main_test_poi(CITY *city) {

    // insert poi
    insert_poi(city, "Salamanca Place");
    insert_poi(city, "MONA");
    insert_poi(city, "Cascade Brewery");
    // remove poi
    remove_poi(city, "MONA");
    // search poi
    search_poi(city, "Cascade Brewery");

    return 0;
}