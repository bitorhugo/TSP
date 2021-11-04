#include "client.h"




int main() {

    Client *head = NULL;


    //insert_new_client_tail(&head);
    //insert_new_client_tail(&head);
    //insert_new_client_head(&head);
    insert_new_client_head(&head);
    print_clients(&head);
    remove_client(&head, 0);
    printf("\n");
    print_clients(&head);

    return 0;
}
