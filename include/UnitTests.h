//
// Created by hekal on 5/11/25.
//
#ifndef UNITTESTS_H
#define UNITTESTS_H
#include <vector>
#include <string>
#include <cassert>
#include <iostream>

#include "ProcessServices.h"

using namespace std;

inline void TestAvgResponseTime() {
    const vector<Process> processes = {
        {"P1", 2, 1, 3},
        {"P3", 2, 2, 5},
        {"P4", 2, 2, 5},
        {"P5", 2, 3, 1},
        {"P2", 3, 1, 5}
    };

    const vector<pair<string, int>> schedule = {
        {"P1", 5},
        {"P2", 10},
        {"P3", 12},
        {"P4", 14},
        {"P3", 16},
        {"P4", 18},
        {"P3", 19},
        {"P4", 20},
        {"P5", 21}
    };

    constexpr double avg_response = 7.6;
    const double calculated_avg = AvgResponseTime(processes, schedule);

    cout << "Unit Test Results:\n";
    cout << "Expected Average Response Time: " << avg_response << "\n";
    cout << "Calculated Average Response Time: " << calculated_avg << "\n";

    if (constexpr double t = 0.01; abs(calculated_avg - avg_response) < t) {
        cout << "TEST PASSED!\n";
    } else {
        cout << "TEST FAILED!\n";
        cerr << "Error: Expected " << avg_response << " but got " << calculated_avg << endl;
    }
}
#endif //UNITTESTS_H
