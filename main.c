#include "client.h"




int main() {

    Client *head = NULL;

    Client *first = create_new_client(&head, 1);
    Client *second = create_new_client(&head,2);
    Client *third = create_new_client(&head, 3);

    first->next_in_line = second;
    second->next_in_line = third;

    print_client(&head, first);
    print_client(&head, second);
    print_client(&head, third);

    return 0;
}
