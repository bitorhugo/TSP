//
// Created by Vitor Hugo on 08/01/2022.
//

#include "test_report.h"

int main_test_report (CLIENT_LL *list) {

    // save clients report
    client_report_txt(list, "../Files/report/report.txt");

    return 0;
}