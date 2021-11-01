#include "client.h"




int main() {

    Client *first = create_new_client(1);
    Client *second = create_new_client(2);
    Client *third = create_new_client(3);

    first->next_in_line = second;
    second->next_in_line = third;

    print_client(first);
    print_client(second);
    print_client(third);

    return 0;
}
