#include "client.h"




int main() {

    Client *head = NULL;
    uint32_t client_id = 0;

    insert_new_client(&head, 0, &client_id);
    insert_new_client(&head, 0, &client_id);
    search_client_by_id(&head, 1);
    search_client_by_id(&head, 2);

    insert_trip_for_client(&head, 1, "Portugal");
    insert_trip_for_client(&head, 1, "Germany");
    print_trips(&head, 1);

    remove_trip_for_client(&head, 1, "Germany");
    print_trips(&head, 1);
    remove_trip_for_client(&head, 1, "Portugal");
    print_trips(&head, 1);
    //edit_trip_for_client(&head, 2, "France", "EstadosUnidos");
    //print_clients(&head);
    //remove_client(&head, 0);
    //print_clients(&head);
    //search_client_by_id(&head, 0);

    free_clients_list(&head);

    return 0;
}
