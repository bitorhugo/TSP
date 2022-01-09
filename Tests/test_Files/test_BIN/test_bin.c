//
// Created by Vitor Hugo on 08/01/2022.
//
#include "test_bin.h"

int main_bin_test(CLIENT_LL *list) {

    // read clients from bin
    read_list_bin(list, "../Files/bin/clients.bin");

    insert_client(list, false, "Bitor Hugo", 245263582, "Rua do Amial Porto", 962321123, 21, 8, 1998);
    book_trip(&list->head->client, "Japan");
    book_trip(&list->head->client, "Belgium");

    insert_city(list->head->client.booked_trips, "Tokyo", 1.3972f, 103.8719f);
    insert_city(list->head->client.booked_trips, "Osaka", 34.7500f, 135.4601f);
    insert_city(list->head->client.booked_trips, "Kyoto", 35.0111f, 135.7669f);

    for (size_t i = 0; i < list->head->client.booked_trips->num_of_cities; ++i) {
        CITY *temp_city = list->head->client.booked_trips->cities + i;
        insert_description(temp_city, "description");
        insert_poi(temp_city, "point of interest");
    }

    finish_trip_requisite(&list->head->client, "Australia");

    // save clients to bin
    save_list_bin(list, "../Files/bin/clients.bin");

    return 0;
}

