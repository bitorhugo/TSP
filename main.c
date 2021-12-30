#include "Client_Linked_List/client_linked_list.h"
#include "main_algorithm.h"

int main() {

    CLIENT_LL client_list;

    // insert client in list
    insert_client(&client_list, false, "Hugo", 123, "Porto", 91912, 21, 8, 1998);
    insert_client(&client_list, false, "Andre", 321, "Lisbon", 9123454, 12, 6, 1899);
    insert_client(&client_list, true, "Carlos", 567, "Faro", 238744, 8, 12, 1989);
    // remove client in list
    //remove_client(&client_list, hugo);
    // search for client in list
    search_client(&client_list, "Andre");
    // print all clients in list
    print_clients(&client_list);

    // book a trip
    insert_trip(&client_list.head->next_node->client, "england");
    insert_trip(&client_list.head->next_node->client, "australia");
    insert_trip(&client_list.head->next_node->client, "usa");
    // remove a booked trip
    remove_trip(&client_list.head->next_node->client, "england");
    // edit a booked trip
    edit_trip(&client_list.head->next_node->client, "australia", "New Zealand");
    // print booked trips
    print_trips(&client_list.head->next_node->client, false);

    // insert city in booked trip
    insert_city(client_list.head->next_node->client.booked_trips, "Sidney", -31.08f, 150.91f);
    insert_city(client_list.head->next_node->client.booked_trips, "Melbourne", -35.35f, 149.23f);
    insert_city(client_list.head->next_node->client.booked_trips, "Darwin", -32.91f, 151.75f);
    insert_city(client_list.head->next_node->client.booked_trips, "Liverpool", -33.92f, 150.92f);
    // remove city from booked trip
    //remove_city(hugo.booked_trips, "Melbourne");
    // search city from booked trip
    search_city(client_list.head->next_node->client.booked_trips, "Darwin");
    // edit city from booked trip
    //edit_city(hugo.booked_trips, "Sidney", "Hobart", 32.4f, 87.5f);

    save_client_txt(&client_list, "../Files/txt/clients.txt");

    initialize_algorithm(client_list.head->next_node->client.booked_trips, 150, 4, 0, 0.05f);
    return 0;
}
