#include "client.h"
#include "ag.h"

int main() {

    Client *head = NULL;
    GENARATION *head_generations = NULL;
    POPULATION *initial_population = NULL;

    insert_new_client(&head, true, 1234);
    insert_new_client(&head, true, 24563);
    insert_new_client(&head, true, 263423);

    print_clients(&head);

    search_client_by_id(&head, 1);
    search_client_by_id(&head, 1234);

    insert_trip(&head, 1234, "portugal");
    insert_trip(&head, 1234, "Germany");
    insert_trip(&head, 1234, "Denmark");
    print_trips(&head, 1234, 0);

    insert_city(&head, 1234, "Portugal", "Porto");
    insert_city(&head, 1234, "Portugal", "Lisbon");
    insert_city(&head, 1234, "Portugal", "Aveiro");
    insert_city(&head, 1234, "Portugal", "Faro");
    insert_city(&head, 1234, "Portugal", "Braga");
    insert_city(&head, 1234, "Germany", "Munich");
    insert_city(&head, 1234, "Germany", "Berlin");
    insert_city(&head, 1234, "Germany", "Be");
    insert_city(&head, 1234, "Germany", "ABC");

    search_city(&head, 1234, "Portugal", "Lisbon");
    search_city(&head, 1234, "Germany", "Be");
    search_city(&head, 1234, "Germany", "ABC");
    search_city(&head, 1234, "Portugal", "Porto");

    insert_PoI(&head, 1234, "Portugal", "Porto", 1.1f, 2.4f);
    insert_PoI(&head, 1234, "Portugal", "Lisbon", 3.2f, 3.5f);
    insert_PoI(&head, 1234, "Portugal", "Aveiro", 13.2f, 45.5f);
    insert_PoI(&head, 1234, "Portugal", "Faro", 7.2f, 4.5f);
    insert_PoI(&head, 1234, "Portugal", "Braga", 32.2f, 23.5f);

    search_PoI(&head, 1234, "Portugal", "Porto");

    sort_clients(&head, 0);

    //print_trips_specific(&head, 1234, "Portugal", "Lisbon", 0);

    print_clients(&head);
    //write_report(&head, 1, false);

    create_population(&head, initial_population, 1234, 4);

    free_clients_list(&head);

    return 0;
}
