//
// Created by Vitor Hugo on 08/01/2022.
//

#include "test_description.h"


int main_test_description(CITY *city) {

    // insert description
    insert_description(city, "capital and most populous city of the Australian island state of Tasmania");
    // edit description
    edit_description(city, "capital and most populous city of the Australian.");

    return 0;
}