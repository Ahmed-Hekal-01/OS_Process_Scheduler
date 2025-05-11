//
// Created by hekal on 5/11/25.
//

#ifndef PROCESSSERVICE_H
#define PROCESSSERVICE_H
#include "bits/stdc++.h"
using namespace std;
struct Process {
    string ID;
    int arrivalTime{};
    int priority{};
    int burstTime{};
    int time_remaining{};
    bool operator==(const Process& other) const {
        return ID == other.ID;
    }
};

inline vector<Process> GenerateProcesses(int n = 5) {
    vector<Process> processes;
    if (n < 3) n = 3;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> arrivalDist(0, 5);
    uniform_int_distribution<> burstDist(1, 5);
    uniform_int_distribution<> closeArrival(0, 1);
    uniform_int_distribution<> priorityDist(1, 3);

    processes.clear();

    for (int priority = 1; priority <= 3; priority++) {
        Process p1;
        p1.ID = "P" + to_string(processes.size() + 1);
        p1.arrivalTime = arrivalDist(gen) % 3;
        p1.priority = priority;
        p1.burstTime = burstDist(gen);
        processes.push_back(p1);

        if (processes.size() < n) {
            Process p2;
            p2.ID = "P" + to_string(processes.size() + 1);
            p2.arrivalTime = p1.arrivalTime + closeArrival(gen);
            p2.priority = priority;
            p2.burstTime = burstDist(gen);
            processes.push_back(p2);
        }
    }

    while (processes.size() < n) {
        Process p;
        p.ID = "P" + to_string(processes.size() + 1);
        p.arrivalTime = arrivalDist(gen);
        p.priority = priorityDist(gen);
        p.burstTime = burstDist(gen);
        processes.push_back(p);
    }

    ranges::sort(processes, [](const Process& a, const Process& b) {
        return a.arrivalTime < b.arrivalTime;
    });

    return processes;
}


inline void PrintProcesses(const vector<Process>& processes) {
    cout << "P\tAr\tPr\tBu\n";
    for (const auto& p : processes) {
        cout << p.ID << "\t" << p.arrivalTime << "\t"
             << p.priority << "\t" << p.burstTime << "\n";
    }
}

#endif
