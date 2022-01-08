//
// Created by Vitor Hugo on 27/12/2021.
//

#include "client_linked_list.h"

#include <stdio.h>
#include <string.h>

/*
 * Private functions prototypes
 */
void sort_clients_id (CLIENT_NODE **head);
void sort_clients_name (CLIENT_LL *list);
void split_list_in_two(CLIENT_NODE * source, CLIENT_NODE ** frontRef, CLIENT_NODE ** backRef);
CLIENT_NODE* sorted_merge(CLIENT_NODE *a, CLIENT_NODE *b);

void read_clients_txt (CLIENT_LL *list, FILE *fp);
void read_trips_txt (CLIENT *client, FILE *fp, bool is_finished);
void read_cities_txt (COUNTRY *country, FILE *fp);
void read_description_txt (CITY *city, FILE *fp);
void read_poi_txt (CITY *city, FILE *fp);

void save_client_txt (CLIENT_LL *list, FILE *fp);
void save_booked_trips_txt (CLIENT *client, FILE *fp);
void save_cities_txt (COUNTRY *country, FILE *fp);
void save_description_txt (CITY *city, FILE *fp);
void save_poi_txt (CITY *city, FILE *fp);

void read_clients_bin (CLIENT_LL *list, FILE *fp);
void read_booked_trips_bin (CLIENT *client, FILE *fp);
void read_cities_bin (COUNTRY *country, FILE *fp);
void read_description_bin (CITY *city, FILE *fp);
void read_poi_bin (CITY *city, FILE *fp);

void save_client_bin (CLIENT_LL *list, FILE *fp);
void save_booked_trips_bin (CLIENT *client, FILE *fp);
void save_cities_bin (COUNTRY *country, FILE *fp);
void save_description_bin (CITY *city, FILE *fp);
void save_poi_bin (CITY *city, FILE *fp);

void deallocate_booked_trips (CLIENT *client);
void deallocate_finished_trips (CLIENT *client);
void deallocate_cities (COUNTRY *country);
void deallocate_poi (CITY *city);
void deallocate_str (char *str);

/*
 * Public functions implementation
 */
void insert_client (CLIENT_LL *list, bool at_head, char *name, uint32_t VAT, char *address, uint32_t phone_number, int birth_day, int birth_month, int birth_year) {
    if (list->list_size < 1) {
        list->head = allocate_memory_node_client();
        list->head->client = create_client(name, VAT, address, phone_number, birth_day, birth_month, birth_year);
        list->list_size = 1;
    }
    else {
        CLIENT_NODE *new_node = allocate_memory_node_client();
        new_node->client = create_client(name, VAT, address, phone_number, birth_day, birth_month, birth_year);

        if (at_head) {
            new_node->next_node = list->head;
            list->head = new_node;
            list->list_size += 1;
        }
        else {
            CLIENT_NODE *temp_node = list->head;
            while (temp_node->next_node != NULL) {
                temp_node = temp_node->next_node;
            }
            temp_node->next_node = new_node;
            list->list_size += 1;
        }
    }
}
void insert_client_sorted (CLIENT_LL *list, char *name, uint32_t VAT, char *address, uint32_t phone_number, int birth_day, int birth_month, int birth_year) {
    if (list->list_size < 1) {
        list->head = allocate_memory_node_client();
        list->head->client = create_client(name, VAT, address, phone_number, birth_day, birth_month, birth_year);
        list->list_size = 1;
    }
    else {
        // makes sure that list is sorted
        sort_clients_id(&list->head);

        CLIENT_NODE *new_node = allocate_memory_node_client();
        new_node->client = create_client(name, VAT, address, phone_number, birth_day, birth_month, birth_year);

        CLIENT_NODE *temp_node = list->head;
        while (temp_node->next_node != NULL) {

            if (temp_node->next_node->client.VAT > new_node->client.VAT) {
                // if new_node is to be inserted at head
                // point head at new_node
                if (temp_node == list->head) {
                    new_node->next_node = temp_node;
                    list->head = new_node;
                    return;
                }
                // insert new_node between temp_node and temp_node->next_node
                new_node->next_node = temp_node->next_node;
                temp_node->next_node = new_node;
                return;
            }

            temp_node = temp_node->next_node;
        }
    }
}
CLIENT* search_client (CLIENT_LL *list, const char *client_name) {
    CLIENT_NODE *temp_node = list->head;
    while (temp_node != NULL) {
        if (strcmp(temp_node->client.name, client_name) == 0){
            printf("Client %s found\n", temp_node->client.name);
            return &temp_node->client;
        }
        temp_node = temp_node->next_node;
    }
    fprintf(stderr, "ERROR: CLIENT NOT FOUND\n");
    return NULL;
}
void remove_client (CLIENT_LL *list, char *client_name) {
    if (list->list_size < 1) {
        fprintf(stderr, "ERROR: NO CLIENTS AVAILABLE\n");
        return;
    }
    CLIENT_NODE *temp_node = list->head;
    while (temp_node != NULL) {
        if (strcmp(temp_node->client.name, client_name) == 0) { // checks if head is to be removed
            list->head = temp_node->next_node;
            deallocate_memory_node_client(temp_node);
            list->list_size -= 1;
            return;
        }
        if (strcmp(temp_node->client.name, client_name) == 0) {
            temp_node->next_node = temp_node->next_node->next_node;
            deallocate_memory_node_client(temp_node->next_node);
            list->list_size -= 1;
            return;
        }
        temp_node = temp_node->next_node;
    }
    fprintf (stderr, "ERROR: CLIENT NOT FOUND\n");
}
void sort_clients (CLIENT_LL *list, short attribute) {
    if (list->list_size < 1) {
        fprintf(stderr, "ERROR: NO CLIENTS AVAILABLE\n");
        return;
    }
    if (attribute == 0) sort_clients_id(&list->head);
    else sort_clients_name(list);
}
void print_clients (CLIENT_LL *list) {
    if (list->list_size < 1) {
        fprintf(stderr, "ERROR: NO CLIENTS AVAILABLE\n");
    }
    CLIENT_NODE *temp_node = list->head;
    while (temp_node != NULL) {
        printf ("Client %d\n", temp_node->client.VAT);
        temp_node = temp_node->next_node;
    }
    printf("..\n");
}

void client_report_txt (CLIENT_LL *list, char *filename) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        fprintf(stderr, "ERROR: NOT ABLE TO OPEN FILE FOR WRITING\n");
        return;
    }

    /*
     * FILE TEMPLATE:
     * Client 'name'
     * booked trips:
     * finished trips
    */

    fprintf (fp, "PORTO PONTOS CLIENTS\n");

    // iterate over every client
    CLIENT_NODE *temp_node = list->head;
    while (temp_node != NULL) {

        fprintf(fp, "Client %s:\n", temp_node->client.name);

        // iterate over clients booked trips
        if (temp_node->client.size_booked_trips > 1){
            fprintf(fp, "Booked trips: ");
            for (size_t i = 0; i < temp_node->client.size_booked_trips; ++i) {
                COUNTRY *temp_country = temp_node->client.booked_trips + i;
                if (i == temp_node->client.size_booked_trips - 1) {
                    fprintf(fp, "%s\n", temp_country->name);
                    break;
                }
                fprintf(fp, "\t%s, ", temp_country->name);
            }
        }

        // iterate over finished trips
        if (temp_node->client.size_finished_trips > 1) {
            fprintf(fp, "Finished trips: ");
            for (size_t i = 0; i < temp_node->client.size_finished_trips; ++i) {
                COUNTRY *temp_country = temp_node->client.finished_trips + i;
                if (i == temp_node->client.size_finished_trips - 1) {
                    fprintf(fp, "%s\n", temp_country->name);
                    break;
                }
                fprintf(fp, "\t%s, ", temp_country->name);
            }
        }

        fprintf(fp, "\n");

        temp_node = temp_node->next_node;
    }
}
void read_list_txt (CLIENT_LL *list, char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "ERROR: NOT ABLE TO OPEN FILE FOR READING\n");
        return;
    }

    /*
     * FILE TEMPLATE
     * 'number of clients'
     *      'name',
     *      'VAT'
     *      'address',
     *      'phone_number'
     *      'birth' (day/month/year)
     *      'number of booked trips'
     *          'trips name',
     *          'num cities'
     *              'cities name',
     *              'coordinate x', 'coordinate y'
     *                  'city description',
     *              'num city poi'
     *                  'poi',
     *      'finished trips',
     */

    // reads clients
    read_clients_txt(list, fp);

    fclose(fp);
}
void save_list_txt (CLIENT_LL *list, char *filename) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        fprintf(stderr, "ERROR: NOT ABLE TO OPEN FILE FOR WRITING\n");
        return;
    }
    /*
     * FILE TEMPLATE
     * 'number of clients'
     *      'name',
     *      'VAT'
     *      'address',
     *      'phone_number'
     *      'birth' (day/month/year)
     *      'number of booked trips'
     *          'trips name',
     *          'num cities'
     *              'cities name',
     *              'coordinate x', 'coordinate y'
     *                  'city description',
     *              'num city poi'
     *                  'poi',
     *      'finished trips',
     */
    // saves clients to file
    save_client_txt(list, fp);

    fclose(fp);
}
void read_list_bin (CLIENT_LL *list, char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        fprintf(stderr, "ERROR: NOT ABLE TO OPEN FILE FOR READING BIN\n");
        return;
    }
    read_clients_bin(list, fp);
    fclose(fp);
}
void save_list_bin (CLIENT_LL *list, char *filename) {
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) {
        fprintf(stderr, "ERROR: NOT ABLE TO OPEN FILE FOR WRITING BIN\n");
        return;
    }
    save_client_bin(list, fp);
    fclose(fp);
}

void deallocate_client_linked_list (CLIENT_LL *list) {

    CLIENT_NODE *temp_node = NULL;

    while (list->head != NULL) {
        temp_node = list->head;
        // set head as next node
        list->head = temp_node->next_node;

        // free client name
        deallocate_str(temp_node->client.name);

        // free client address
        deallocate_str(temp_node->client.address);

        // free booked trips
        deallocate_booked_trips(&temp_node->client);

        // free finished trips
        deallocate_finished_trips(&temp_node->client);

        // free client node
        deallocate_memory_node_client(temp_node);
    }
}

/*
 * Private functions implementation
 */
void read_clients_txt (CLIENT_LL *list, FILE *fp) {
    // read number of clients
    int num_clients = 0;
    fscanf(fp, "%d", &num_clients);

    for (size_t i = 0; i < num_clients; ++i) {
        // save insert name
        char name [50] = "";
        fscanf(fp, "%*c %[^,]", name);

        // save VAT
        uint32_t vat = 0;
        fscanf(fp, "%*c %d", &vat);

        // save address
        char address [100] = "";
        fscanf(fp, "%*[\n] %[^,]", address);

        // save phone_number
        uint32_t phone_number = 0;
        fscanf(fp, "%*c %d", &phone_number);

        // save birth (day/month/year)
        DATE birth = {0};
        fscanf(fp, "%d %*c %d %*c %d", &birth.day, &birth.month, &birth.year);

        // insert client
        insert_client(list, false, name, vat, address, phone_number, birth.day, birth.month, birth.year);

        // get client
        CLIENT *temp_client = search_client(list, name);

        // reads booked trips
        read_trips_txt(temp_client, fp, false);
    }
}
void read_trips_txt (CLIENT *client, FILE *fp, bool is_finished) {
    if (is_finished) {
        // read number of finished trips
        int num_trips = 0;
        fscanf(fp, "%d", &num_trips);

        for (size_t i = 0; i < num_trips; ++i) {
            // save trip name
            char country_name [50] = "";
            fscanf(fp, "%*[\n] %[^,]", country_name);

        }
    }
    else {
        int num_trips = 0;
        fscanf(fp, "%d", &num_trips);

        for (size_t i = 0; i < num_trips; ++i) {
            char country_name [50] = "";
            fscanf(fp, "%*c %[^,]", country_name);

            // book a trip
            book_trip(client, country_name);

            // get a trip
            COUNTRY *temp_country = search_trip(client, country_name, false);

            // reads cities
            read_cities_txt(temp_country, fp);
        }
    }

}
void read_cities_txt (COUNTRY *country, FILE *fp) {
    // read number of cities
    int num_cities = 0;
    fscanf(fp, "%*c %d", &num_cities);

    for (size_t i = 0; i < num_cities; ++i) {
        // save city name
        char city_name [50] = "";
        fscanf(fp, "%*c %[^,]", city_name);

        // save coordinates
        POINTS coordinates = {0};
        fscanf(fp, "%*c %f %*c %f", &coordinates.x, &coordinates.y);

        // insert city
        insert_city(country, city_name, coordinates.x, coordinates.y);

        // get city
        CITY *temp_city = search_city(country, city_name);

        // read description
        read_description_txt(temp_city, fp);

        // read poi
        read_poi_txt(temp_city, fp);

    }
}
void read_description_txt (CITY *city, FILE *fp) {
    // save description
    char description [200] = "";
    fscanf(fp, "%*[\n] %[^,]", description);

    // insert description
    insert_description(city, description);
}
void read_poi_txt (CITY *city, FILE *fp) {
    // save num poi
    int num_poi = 0;
    fscanf(fp, "%*c %d", &num_poi);

    for (size_t i = 0; i < num_poi; ++i) {
        // save poi
        char poi [100] = "";

        if (i == 0) {
            fscanf(fp, "%*[\n] %[^,]", poi);
        }
        else {
            fscanf(fp, "%*c %[^,]", poi);
        }
        insert_poi(city, poi);
    }

}

void save_client_txt (CLIENT_LL *list, FILE *fp) {
    // save number of clients
    fprintf(fp, "%d\n", list->list_size);

    CLIENT_NODE *temp_node = list->head;
    while (temp_node != NULL) {

        // save client name
        fprintf(fp, "%s,\n", temp_node->client.name);

        // save client VAT
        fprintf(fp, "%d\n", temp_node->client.VAT);

        // save client address
        fprintf(fp, "%s,\n", temp_node->client.address);

        // save phone number
        fprintf(fp, "%d\n", temp_node->client.phone_number);

        // save birth
        fprintf(fp, "%d/%d/%d\n", temp_node->client.birth.day, temp_node->client.birth.month, temp_node->client.birth.year);

        // save booked trips
        save_booked_trips_txt (&temp_node->client, fp);

        temp_node = temp_node->next_node;
    }
}
void save_booked_trips_txt (CLIENT *client, FILE *fp) {

    // save number booked trips
    fprintf(fp, "%d\n", client->size_booked_trips);

    for (size_t i = 0; i < client->size_booked_trips; ++i) {
        COUNTRY *temp_country = client->booked_trips + i;

        // save trip name
        fprintf(fp, "%s,\n", temp_country->name);

        // save cities
        save_cities_txt (temp_country, fp);
    }

}
void save_cities_txt (COUNTRY *country, FILE *fp) {
    // save number of cities
    fprintf(fp, "%d\n", country->num_of_cities);

    for (size_t i = 0; i < country->num_of_cities; ++i) {
        CITY *temp_city = country->cities + i;
        // save city name
        fprintf(fp, "%s,\n", temp_city->name);

        // save coordinates
        fprintf(fp, "%f, %f\n", temp_city->coordinates.x, temp_city->coordinates.y);

        // save description
        save_description_txt (temp_city, fp);

        // save poi
        save_poi_txt (temp_city, fp);
    }
}
void save_description_txt (CITY *city, FILE *fp) {
    // save description
    fprintf(fp, "%s,\n", city->description);
}
void save_poi_txt (CITY *city, FILE *fp) {
    // save number of poi
    fprintf(fp, "%d\n", city->num_of_poi);

    for (size_t i = 0; i < city->num_of_poi; ++i) {
        POI *temp_poi = city->poi + i;
        // save poi
        fprintf(fp, "%s,\n", temp_poi->name);
    }
}

void read_clients_bin (CLIENT_LL *list, FILE *fp) {
    // read number of clients
    int num_clients = 0;
    fread(&num_clients, sizeof(int), 1, fp);

    for (size_t i = 0; i < num_clients; ++i) {
        // read client name size
        uint64_t name_size = fread(&name_size, sizeof(uint64_t), 1, fp);
        // read client name
        char name [50] = "";
        fread(name, sizeof(char), name_size, fp);

        // read vat
        uint32_t vat = 0;
        fread(&vat, sizeof(uint32_t), 1, fp);

        // read address
        uint64_t add_size = 0;
        fread(&add_size, sizeof(uint64_t), 1, fp);
        char address [100] = "";
        fread(address, sizeof(char), add_size, fp);

        // read phone number
        uint32_t phone_number = 0;
        fread(&phone_number, sizeof(uint32_t), 1, fp);

        // read birth date
        int day = 0;
        int month = 0;
        int year = 0;
        fread(&day, sizeof(int), 1, fp);
        fread(&month, sizeof(int), 1, fp);
        fread(&year, sizeof(int), 1, fp);

        // insert client
        insert_client(list, false, name, vat, address, phone_number, day, month, year);

        // search for client
        CLIENT *temp_client = search_client(list, name);

        // read booked trips
        read_booked_trips_bin(temp_client, fp);
    }
}
void read_booked_trips_bin (CLIENT *client, FILE *fp) {
    // read number of trips
    int num_booked_trips = 0;
    fread(&num_booked_trips, sizeof(int), 1, fp);

    for (size_t i = 0; i < num_booked_trips; ++i) {
        // read booked trip name
        uint64_t booked_trip_name_size = 0;
        fread(&booked_trip_name_size, sizeof(uint64_t), 1, fp);
        char booked_trip_name [50] = "";
        fread(booked_trip_name, sizeof(char), booked_trip_name_size, fp);

        // insert booked trip
        book_trip(client, booked_trip_name);

        // search booked trip
        COUNTRY *temp_country = search_trip(client, booked_trip_name, false);

        // read cities
        read_cities_bin(temp_country, fp);
    }
}
void read_cities_bin (COUNTRY *country, FILE *fp) {
    // read number of cities
    int num_cities = 0;
    fread(&num_cities, sizeof(int), 1, fp);

    for (size_t i = 0; i < num_cities; ++i) {
        // read city name
        uint64_t city_name_size = 0;
        fread(&city_name_size, sizeof(uint64_t), 1, fp);
        char city_name [50] = "";
        fread(city_name, sizeof(char), city_name_size, fp);

        // read coordinates
        float x = 0, y = 0;
        fread(&x, sizeof(float), 1, fp);
        fread(&y, sizeof(float), 1, fp);

        // insert city
        insert_city(country, city_name, x, y);

        // search city
        CITY *temp_city = search_city(country, city_name);

        // read description
        read_description_bin(temp_city, fp);

        // read poi
        read_poi_bin(temp_city, fp);
    }
}
void read_description_bin (CITY *city, FILE *fp) {
    // read description
    uint64_t des_size = 0;
    fread(&des_size, sizeof(uint64_t), 1, fp);
    char description [200] = "";
    fread(description, sizeof(char), des_size, fp);

    // insert description
    insert_description(city, description);
}
void read_poi_bin (CITY *city, FILE *fp) {
    // read number of poi
    int num_poi = 0;
    fread(&num_poi, sizeof(int), 1, fp);

    for (size_t i = 0; i < num_poi; ++i) {
        // read poi
        uint64_t poi_size = 0;
        fread(&poi_size, sizeof(uint64_t), 1, fp);
        char poi [100] = "";
        fread(poi, sizeof(char), poi_size, fp);

        // insert poi
        insert_poi(city, poi);
    }
}

void save_client_bin (CLIENT_LL *list, FILE *fp) {
    // save number of clients
    int num_clients = list->list_size;
    fwrite(&num_clients, sizeof(int), 1, fp);

    CLIENT_NODE *temp_node = list->head;
    while (temp_node != NULL) {

        // save client name size
        uint64_t client_name_size = strlen(temp_node->client.name) + 1;
        fwrite(&client_name_size, sizeof(uint64_t), 1, fp);
        // save client name
        fwrite(temp_node->client.name, sizeof(char), client_name_size, fp);

        // save client VAT
        uint32_t vat = temp_node->client.VAT;
        fwrite(&vat, sizeof(uint32_t), 1, fp);

        // save address size
        uint64_t client_address_size = strlen(temp_node->client.address) + 1;
        fwrite(&client_address_size, sizeof(uint64_t), 1, fp);
        // save address
        fwrite(temp_node->client.address, sizeof(char), client_address_size, fp);

        // save phone number
        uint32_t phone_number = temp_node->client.phone_number;
        fwrite(&phone_number, sizeof(uint32_t), 1, fp);

        // save birth
        int client_birth_day = temp_node->client.birth.day;
        int client_birth_month = temp_node->client.birth.month;
        int client_birth_year = temp_node->client.birth.year;
        fwrite(&client_birth_day, sizeof(int), 1, fp);
        fwrite(&client_birth_month, sizeof(int), 1, fp);
        fwrite(&client_birth_year, sizeof(int), 1, fp);

        // save booked trips bin
        save_booked_trips_bin(&temp_node->client, fp);

        temp_node = temp_node->next_node;
    }
}
void save_booked_trips_bin (CLIENT *client, FILE *fp) {
    // save number of booked trips
    int booked_trips_size = client->size_booked_trips;
    fwrite(&booked_trips_size, sizeof(int), 1, fp);

    for (size_t i = 0; i < client->size_booked_trips; ++i) {
        COUNTRY *temp_country = client->booked_trips + i;

        // save trip name
        uint64_t booked_trip_name_size = strlen(temp_country->name) + 1;
        fwrite(&booked_trips_size, sizeof(uint64_t), 1, fp);
        fwrite(temp_country->name, sizeof(char), booked_trips_size, fp);

        save_cities_bin(temp_country, fp);

    }
}
void save_cities_bin (COUNTRY *country, FILE *fp) {
    // save number of cities
    int num_cities = country->num_of_cities;
    fwrite(&num_cities, sizeof(int), 1, fp);

    for (size_t i = 0; i < country->num_of_cities; ++i) {
        CITY *temp_city = country->cities + i;

        // save city name
        uint64_t city_name_size = strlen(temp_city->name) + 1;
        fwrite(&city_name_size, sizeof(uint64_t), 1, fp);
        fwrite(temp_city->name, sizeof(char), city_name_size, fp);

        // save city coordinates
        float x = temp_city->coordinates.x;
        float y = temp_city->coordinates.y;
        fwrite(&x, sizeof(float), 1, fp);
        fwrite(&y, sizeof(float), 1, fp);

        // save description
        save_description_bin(temp_city, fp);

        // save poi
        save_poi_bin(temp_city, fp);
    }
}
void save_description_bin (CITY *city, FILE *fp) {
    // save description
    uint64_t des_size = strlen(city->description) + 1;
    fwrite(&des_size, sizeof(uint64_t), 1, fp);
    fwrite(city->description, sizeof(char), des_size, fp);
}
void save_poi_bin (CITY *city, FILE *fp) {
    // save number poi
    int num_poi = city->num_of_poi;
    fwrite(&num_poi, sizeof(int), 1, fp);

    for (size_t i = 0; i < city->num_of_poi; ++i) {
        POI * temp_poi = city->poi + i;
        // save poi
        uint64_t poi_size = strlen(temp_poi->name) + 1;
        fwrite(&poi_size, sizeof(uint64_t), 1, fp);
        fwrite(temp_poi->name, sizeof(char), poi_size, fp);
    }
}

void sort_clients_id (CLIENT_NODE **head) {
    // base case — length 0 or 1
    if (*head == NULL || (*head)->next_node == NULL) {
        return;
    }

    CLIENT_NODE *a;
    CLIENT_NODE *b;

    // split `head` into `a` and `b` sublists
    split_list_in_two(*head, &a, &b);

    // recursively sort the sublists
    sort_clients_id(&a);
    sort_clients_id(&b);

    // answer = merge the two sorted lists
    *head = sorted_merge(a, b);
}
void sort_clients_name (CLIENT_LL *list) {

}

void deallocate_booked_trips (CLIENT *client) {
    // start from the end of the array since first element is equal to &booked_trips
    // if we were to start from the beginning of the array
    // we wouldn't be able to access booked trip elements after the first one is deallocated
    if (client->size_booked_trips > 0) {
        for (int i = client->size_booked_trips - 1; i >= 0; --i) {
            COUNTRY *temp_country = client->booked_trips + i;
            deallocate_str(temp_country->name);
            deallocate_cities(temp_country);
        }
        free (client->booked_trips);
    }
}
void deallocate_finished_trips (CLIENT *client) {
    if (client->size_finished_trips > 0) {
        for (int i = client->size_finished_trips - 1; i >= 0; --i) {
            COUNTRY *temp_country = client->finished_trips + i;
            deallocate_str(temp_country->name);
            deallocate_cities(temp_country);
        }
        free (client->finished_trips);
    }
}
void deallocate_cities (COUNTRY *country) {
    if (country->num_of_cities > 0) {
        for (int i = country->num_of_cities - 1; i >= 0; --i) {
            CITY *tem_city = country->cities + i;

            deallocate_str(tem_city->name);

            if (tem_city->num_of_poi > 1) {
                deallocate_poi(tem_city);
            }
            if (tem_city->description != NULL) {
                deallocate_str(tem_city->description);
            }
        }
        free (country->cities);
    }
}
void deallocate_poi (CITY *city) {
    for (int i = city->num_of_poi - 1; i >= 0; --i) {
        POI *temp_poi = city->poi + i;
        deallocate_str(temp_poi->name);
    }
    free (city->poi);
}
void deallocate_str (char *str) {
    free (str);
}

void split_list_in_two(CLIENT_NODE * source, CLIENT_NODE ** frontRef, CLIENT_NODE ** backRef)
{
    // if the length is less than 2, handle it separately
    if (source == NULL || source->next_node == NULL)
    {
        *frontRef = source;
        *backRef = NULL;
        return;
    }

    CLIENT_NODE * slow = source;
    CLIENT_NODE * fast = source->next_node;

    // advance `fast` two nodes, and advance `slow` one node
    while (fast != NULL)
    {
        fast = fast->next_node;
        if (fast != NULL)
        {
            slow = slow->next_node;
            fast = fast->next_node;
        }
    }

    // `slow` is before the midpoint in the list, so split it in two
    // at that point.
    *frontRef = source;
    *backRef = slow->next_node;
    slow->next_node = NULL;
}
CLIENT_NODE* sorted_merge(CLIENT_NODE *a, CLIENT_NODE *b)
{
    // base cases
    if (a == NULL) {
        return b;
    }

    else if (b == NULL) {
        return a;
    }

    CLIENT_NODE *result = NULL;

    // pick either `a` or `b`, and recur
    if (a->client.VAT <= b->client.VAT)
    {
        result = a;
        result->next_node = sorted_merge(a->next_node, b);
    }
    else {
        result = b;
        result->next_node = sorted_merge(a, b->next_node);
    }

    return result;
}