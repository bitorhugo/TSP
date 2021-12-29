#include "Client_Linked_List/client_linked_list.h"
#include "main_algorithm.h"

int main() {

    CLIENT_LL client_list;

    // create client
    CLIENT hugo = create_client("Hugo", 123, "Porto", 91912, 21, 8, 1998);
    CLIENT andre = create_client("Andre", 321, "Lisbon", 9123454, 12, 6, 1899);
    CLIENT carlos = create_client("Carlos", 567, "Faro", 238744, 8, 12, 1989);

    // insert client in list
    insert_client(&client_list, false, hugo);
    insert_client(&client_list, false, andre);
    insert_client(&client_list, true, carlos);
    // remove client in list
    remove_client(&client_list, hugo);
    // search for client in list
    search_client(&client_list, "Andre");
    // print all clients in list
    print_clients(&client_list);

    // book a trip
    insert_trip(&hugo, "england");
    insert_trip(&hugo, "australia");
    insert_trip(&hugo, "usa");
    // remove a booked trip
    remove_trip(&hugo, "england");
    // edit a booked trip
    edit_trip(&hugo, "australia", "New Zealand");
    // print booked trips
    print_trips(&hugo, false);

    // insert city in booked trip
    insert_city(hugo.booked_trips, "Sidney", -31.08f, 150.91f);
    insert_city(hugo.booked_trips, "Melbourne", -35.35f, 149.23f);
    insert_city(hugo.booked_trips, "Darwin", -32.91f, 151.75f);
    insert_city(hugo.booked_trips, "Liverpool", -33.92f, 150.92f);
    // remove city from booked trip
    //remove_city(hugo.booked_trips, "Melbourne");
    // search city from booked trip
    search_city(hugo.booked_trips, "Darwin");
    // edit city from booked trip
    //edit_city(hugo.booked_trips, "Sidney", "Hobart", 32.4f, 87.5f);

    initialize_algorithm(hugo.booked_trips, 150, 4, 0, 0.05f);
    return 0;
}
