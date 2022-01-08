#include "Client_Linked_List/client_linked_list.h"
#include "main_algorithm.h"

int main() {

    CLIENT_LL client_list;

    // read clients from txt
    //read_list_txt(&client_list, "../Files/txt/clients.txt");

    // insert client in list
    insert_client(&client_list, false, "Hugo", 1, "Porto", 91912, 21, 8, 1998);
    insert_client(&client_list, false, "Andre", 4, "Lisbon", 9123454, 12, 6, 1899);
    insert_client(&client_list, false, "Carlos", 6, "Faro", 238744, 8, 12, 1989);
    insert_client_sorted(&client_list, "Afonso", 5, "Viana", 92834, 21, 4, 1998);
    // remove client in list
    remove_client(&client_list, "Joao");
    // search for client in list
    search_client(&client_list, "Andre");
    // print all clients in list
    print_clients(&client_list);
    // sort clients
    sort_clients(&client_list, 0);
    // print all clients
    print_clients(&client_list);

    // book a trip
    book_trip(&client_list.head->next_node->client, "england");
    book_trip(&client_list.head->next_node->client, "australia");
    book_trip(&client_list.head->next_node->client, "usa");
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
    remove_city(client_list.head->next_node->client.booked_trips , "Denver");
    // search city from booked trip
    search_city(client_list.head->next_node->client.booked_trips, "Darwin");
    // edit city from booked trip
    edit_city(client_list.head->next_node->client.booked_trips, "Sidney", "Hobart", 32.4f, 87.5f);
    // insert city description
    insert_description(client_list.head->next_node->client.booked_trips->cities, "capital and most populous city of the Australian island state of Tasmania");
    edit_description(client_list.head->next_node->client.booked_trips->cities, "capital and most populous city of the Australian.");
    // insert poi
    insert_poi(client_list.head->next_node->client.booked_trips->cities, "Salamanca Place");
    insert_poi(client_list.head->next_node->client.booked_trips->cities, "MONA");
    insert_poi(client_list.head->next_node->client.booked_trips->cities, "Cascade Brewery");
    // remove poi
    remove_poi(client_list.head->next_node->client.booked_trips->cities, "MONA");
    // search poi
    search_poi(client_list.head->next_node->client.booked_trips->cities, "Cascade Brewery");

    // save clients info and trips to txt file
    client_report_txt(&client_list, "../Files/txt/report.txt");

    // find best route to take for a certain trip
    initialize_algorithm(client_list.head->next_node->client.booked_trips, 999, 4, 0, 0.05f);

    // finish a trip
    finish_trip(&client_list.head->next_node->client, client_list.head->next_node->client.booked_trips);

    // deallocates clients linked list
    deallocate_client_linked_list(&client_list);

    return 0;
}
