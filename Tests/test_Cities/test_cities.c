//
// Created by Vitor Hugo on 08/01/2022.
//

#include "test_cities.h"


int main_test_cities(COUNTRY *country) {

    // insert city
    insert_city(country, "Sidney", -31.08f, 150.91f);
    insert_city(country, "Melbourne", -35.35f, 149.23f);
    insert_city(country, "Darwin", -32.91f, 151.75f);
    insert_city(country, "Liverpool", -33.92f, 150.92f);
    // remove city from booked trip
    remove_city(country, "Denver");
    // search city from booked trip
    search_city(country, "Darwin");
    // edit city from booked trip
    edit_city(country, "Sidney", "Hobart", -32.4f, 87.5f);

    return 0;
}