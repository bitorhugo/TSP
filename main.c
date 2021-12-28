#include "Client_Linked_List/client_linked_list.h"
//#include "client.h"
//#include "ag.h"

int main() {
/*
    CLIENT *head = NULL;

    insert_new_client(&head, true, 1234);
    insert_new_client(&head, true, 24563);
    insert_new_client(&head, true, 263423);
    print_clients(&head);

    search_client_by_id(&head, 1);
    CLIENT *one = search_client_by_id(&head, 1234);

    insert_trip(one, "portugal");
    insert_trip(one, "Germany");
    insert_trip(one, "Denmark");
    print_trips(one, false);

    insert_city(one->trips_to_be_made, "Porto");
    insert_city(one->trips_to_be_made, "Lisbon");
    insert_city(one->trips_to_be_made, "Aveiro");
    insert_city(one->trips_to_be_made, "Braga");
    insert_city(one->trips_to_be_made, "Faro");
    insert_city(one->trips_to_be_made, "Viana");

    CITY *temp_city_one;
    for (int i = 0; i < one->trips_to_be_made->size_trip_cities; ++i) {
        temp_city_one = one->trips_to_be_made->cities + i;
        float x = float_rand(1.0f, 50.0f);
        float y = float_rand(1.0f, 50.0f);
        insert_coordinates(temp_city_one, x, y);
    }

    search_city(one->trips_to_be_made, "Porto");
    search_city(one->trips_to_be_made, "Lisbon");

    insert_PoI(one->trips_to_be_made->cities, "Torre dos Clerigos");
    insert_PoI(one->trips_to_be_made->cities, "Torre dos ");
    insert_PoI(one->trips_to_be_made->cities, "Torre Clerigos");
    //sort_clients(&head, 0);

    //print_trips_specific(&head, 1234, "Portugal", "Lisbon", 0);

    //print_clients(&head);
    //write_report(&head, 1, false);
    //create_population(&head, initial_population, 1234, 4);


    intialize_genetic_algorithm(one->trips_to_be_made, 5, 8, 4, 0.01f);

    free_clients_list(&head);
*/

    CLIENT_LL client_list;

    // create client
    CLIENT hugo = create_client("Hugo", 123, "Porto", 91912, 21, 8, 1998);
    CLIENT andre;
    CLIENT carlos;

    // insert client in list
    insert_client(&client_list, false, hugo);
    insert_client(&client_list, false, andre);
    insert_client(&client_list, true, carlos);
    // remove client in list
    remove_client(&client_list, hugo);
    // search for client in list
    CLIENT temp = search_client(&client_list, andre);
    // print all clients in list
    print_clients(&client_list);

    return 0;
}
