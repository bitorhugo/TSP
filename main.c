#include "client.h"

int main() {

    Client *head = NULL;
    uint32_t num_client = 0;

    insert_new_client(&head, 0, &num_client);
    insert_new_client(&head, 0, &num_client);
    search_client_by_id(&head, 1);
    search_client_by_id(&head, 2);

    insert_trip_for_client(&head, 1, "Portugal");
    insert_trip_for_client(&head, 1, "Germany");
    insert_trip_for_client(&head, 1, "Denmark");
    print_trips(&head, 1);

    insert_trip_city(&head, 1, "Portugal", "Porto");
    insert_trip_city(&head, 1, "Portugal", "Lisbon");
    insert_trip_city(&head, 1, "Germany", "Munich");
    insert_trip_city(&head, 1, "Germany", "Berlin");
    insert_trip_city(&head, 1, "Germany", "Be");
    insert_trip_city(&head, 1, "Germany", "ABC");

    search_trip_city(&head, 1, "Portugal", "Lisbon");
    search_trip_city(&head, 1, "Germany", "Be");
    search_trip_city(&head, 1, "Germany", "ABC");
    search_trip_city(&head, 1, "Portugal", "Porto");

    insert_PoI(&head, 1, "Portugal", "Porto", 1.1, 2.4);
    insert_PoI(&head, 1, "Portugal", "Lisbon", 3.2, 3.5);
    free_clients_list(&head);

    return 0;
}
