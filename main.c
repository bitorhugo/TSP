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

    COUNTRY *temp_country_one = one->trips_to_be_made + 1;

    insert_city(one->trips_to_be_made, "Porto");
    insert_city(one->trips_to_be_made, "Lisbon");
    insert_city(temp_country_one, "Berlin");

    search_city(one->trips_to_be_made, "Porto");
    search_city(one->trips_to_be_made, "Lisbon");

    insert_coordinates(one->trips_to_be_made->cities, 2.2f, 1.2f);
    edit_coordinates(one->trips_to_be_made->cities, 3.0f, 4.0f);
    remove_coordinates(one->trips_to_be_made->cities);
    search_coordinates(one->trips_to_be_made->cities);
    insert_coordinates(one->trips_to_be_made->cities, 2.2f, 1.2f);
    search_coordinates(one->trips_to_be_made->cities);

    insert_PoI(one->trips_to_be_made->cities, "Torre dos Clerigos");

    //sort_clients(&head, 0);

    //print_trips_specific(&head, 1234, "Portugal", "Lisbon", 0);

    //print_clients(&head);
    //write_report(&head, 1, false);
    //create_population(&head, initial_population, 1234, 4);

    free_clients_list(&head);

    return 0;
}
