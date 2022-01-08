//
// Created by Vitor Hugo on 08/01/2022.
//

#include "test_booked_trips.h"

int main_test_booked_trips (CLIENT *client) {

    // book a trip
    book_trip(client, "England");
    book_trip(client, "Australia");
    book_trip(client, "Brazil");
    // remove a booked trip
    remove_trip(client, "Austria");
    // edit a booked trip
    edit_trip(client, "Australia", "New Zealand");
    // print booked trips
    print_trips(client, false);

    return 0;
}