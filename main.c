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
    print_trips(&head, 1);

    remove_trip_for_client(&head, 1, "Germany");
    print_trips(&head, 1);
    //remove_trip_for_client(&head, 1, "Portugal");
    print_trips(&head, 1);
    insert_trip_city(&head, 1, "Portugal", "Porto");
    //print_clients(&head);
    //remove_client(&head, 0);
    //print_clients(&head);
    free_clients_list(&head);

    return 0;
}
