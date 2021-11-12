#include "client.h"




int main() {

    Client *head = NULL;

    insert_new_client(&head, 0);
    insert_new_client(&head, 1);
    insert_new_client(&head, 0);
    insert_new_client(&head, 1);

    create_trip_for_client(&head, 0, "Portugal");
    create_trip_for_client(&head, 0, "Germany");
    //print_clients(&head);
    //remove_client(&head, 0);
    //print_clients(&head);
    //search_client_by_id(&head, 0);

    free_clients_list(&head);

    return 0;
}
