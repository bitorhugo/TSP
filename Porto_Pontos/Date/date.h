//
// Created by Vitor Hugo on 27/12/2021.
//

#ifndef TSP_DATE_H
#define TSP_DATE_H

typedef struct date {
    int day;
    int month;
    int year;
}DATE;

DATE insert_registration_day ();
DATE insert_birth (int day, int month, int year);

#endif //TSP_DATE_H
