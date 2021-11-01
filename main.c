#include "client.h"




int main() {

    Client *head = NULL;

    insert_new_client_head(&head);
    insert_new_client_head(&head);
    insert_new_client_tail(&head);
    insert_new_client_tail(&head);

    print_clients(head);


    return 0;
}
