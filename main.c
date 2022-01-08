#include "Client_Linked_List/client_linked_list.h"

#include "main_algorithm.h"

#include "test_Files/test_BIN/test_bin.h"
#include "test_Files/test_Report/test_report.h"
#include "test_Files/test_TXT/test_txt.h"

#include "test_Client_List/test_client_list.h"

#include "test_Trips/test_Booked_Trips/test_booked_trips.h"

#include "test_Cities/test_cities.h"
#include "test_Description/test_description.h"
#include "test_POI/test_poi.h"


int main() {

    CLIENT_LL client_list;

    // test files
    //main_bin_test(&client_list);
    //main_txt_test(&client_list);

    // test client linked list
    main_client_list_test(&client_list);

    // test booking a trip
    main_test_booked_trips(&client_list.head->client);

    // test cities
    main_test_cities(client_list.head->client.booked_trips);

    // test description
    main_test_description(client_list.head->client.booked_trips->cities);

    // test poi
    main_test_poi(client_list.head->client.booked_trips->cities);

    // save clients info and trips to txt file
    main_test_report(&client_list);

    // find best route to take for a certain trip
    initialize_algorithm(client_list.head->next_node->client.booked_trips, 999, 4, 0, 0.05f);

    // deallocates clients linked list
    deallocate_client_linked_list(&client_list);

    return 0;
}
