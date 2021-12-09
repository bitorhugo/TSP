#include "client.h"
#include "ag.h"

int main() {

    CLIENT *head = NULL;
    //GENARATION *head_generations = NULL;
    //POPULATION *initial_population = NULL;

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

    create_initial_population(one->trips_to_be_made, 2);

    //sort_clients(&head, 0);

    //print_trips_specific(&head, 1234, "Portugal", "Lisbon", 0);

    //print_clients(&head);
    //write_report(&head, 1, false);
    //create_population(&head, initial_population, 1234, 4);

    free_clients_list(&head);

    return 0;
}
