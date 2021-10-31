#include "client.h"




int main() {

    struct sClient *first = create_new_client(1);
    struct sClient *second = create_new_client(2);
//    first->next_in_line = second;

    print_client(first);
    print_client(second);

    return 0;
}
