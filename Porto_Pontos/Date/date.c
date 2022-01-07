//
// Created by Vitor Hugo on 27/12/2021.
//

#include "date.h"
#include <time.h>


DATE insert_registration_day () {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    DATE new_registration = {0};

    new_registration.day = tm.tm_mday;
    new_registration.month = tm.tm_mon + 1;
    new_registration.year = tm.tm_year + 1900;

    return new_registration;
}

DATE create_date (int day, int month, int year) {
    DATE new_date = {0};

    new_date.day = day;
    new_date.month = month;
    new_date.year = year;

    return new_date;
}