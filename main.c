#include "client.h"




int main() {

    Client *head = NULL;


    insert_new_client_tail(&head);
    insert_new_client_tail(&head);
    insert_new_client_head(&head);
    insert_new_client_head(&head);
    create_trip_for_client(&head, 0, "Porto");
    create_trip_for_client(&head, 0, "Lisbon");
    //print_clients(&head);
    //remove_client(&head, 0);
    //print_clients(&head);
    //search_client_by_id(&head, 0);

    //free_clients_list(&head);

    return 0;
}
