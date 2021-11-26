#include "Client/client.h"

int main() {

    Client *head = NULL;
    uint32_t num_client = 0;

    insert_new_client(&head, 0, &num_client);
    insert_new_client(&head, 0, &num_client);

    search_client_by_id(&head, 1);
    search_client_by_id(&head, 2);

    insert_trip(&head, 1, "Portugal");
    insert_trip(&head, 1, "Germany");
    insert_trip(&head, 1, "Denmark");
    print_trips(&head, 1, 0);

    insert_city(&head, 1, "Portugal", "Porto");
    insert_city(&head, 1, "Portugal", "Lisbon");
    insert_city(&head, 1, "Germany", "Munich");
    insert_city(&head, 1, "Germany", "Berlin");
    insert_city(&head, 1, "Germany", "Be");
    insert_city(&head, 1, "Germany", "ABC");

    search_city(&head, 1, "Portugal", "Lisbon");
    search_city(&head, 1, "Germany", "Be");
    search_city(&head, 1, "Germany", "ABC");
    search_city(&head, 1, "Portugal", "Porto");

    insert_PoI(&head, 1, "Portugal", "Porto", 1.1f, 2.4f);
    insert_PoI(&head, 1, "Portugal", "Lisbon", 3.2f, 3.5f);

    search_PoI(&head, 1, "Portugal", "Porto");

    print_trips_specific(&head, 1, "Portugal", "Lisbon", 0);

    write_report(&head, 1);

    free_clients_list(&head);

    return 0;
}
