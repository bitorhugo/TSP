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

/**
 * inserts the day/month/year of a client is inserted
 * @return date of registration
 */
DATE insert_registration_day();
/**
 * creates a date (day/month/year)
 * @param day day
 * @param month month
 * @param year year
 * @return date
 */
DATE create_date (int day, int month, int year);

#endif //TSP_DATE_H
