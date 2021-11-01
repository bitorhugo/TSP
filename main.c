#include "client.h"




int main() {

    Client *head = NULL;


    Client *first = post_new_client(&head, 0);
    Client *second = post_new_client(&head,1);
    Client *third = post_new_client(&head, 2);

    first->next_in_line = second;
    second->next_in_line = third;

    print_client(&head, first);
    print_client(&head, second);
    print_client(&head, third);

    insert_new_client_head(&head);

    print_client(&head, first);
    print_client(&head, second);
    print_client(&head, third);

    insert_new_client_tail(&head);

    print_client(&head, first);
    print_client(&head, second);
    print_client(&head, third);

    return 0;
}
