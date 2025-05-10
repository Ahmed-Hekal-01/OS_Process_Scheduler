//
// Created by hekal on 5/10/25.
//
#ifndef SCHEDULERSERVICES_H
#define SCHEDULERSERVICES_H
#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include <map>
#include <set>
#include<queue>
#include <bits/ranges_algo.h>
using namespace std;
#ifdef _WIN32
#include <windows.h>
#endif

struct Process {
    string ID;
    int arrivalTime;
    int priority;
    int burstTime;
    int time_remaining;
    bool operator==(const Process& other) const {
        return ID == other.ID;  // Compare processes by their ID
    }
};
//
// vector<pair<string, int>> ganttChart;// {ProcessID, EndTime}
  vector<Process> GenerateProcesses(int n = 5) {
    vector<Process> processes;
    if (n < 3) n = 3;  // Minimum 3 processes for 2 priorities
    srand(time(0));
    processes.clear();  // Clear existing processes

    // Create guaranteed priority pairs
    for (int priority = 1; priority <= 3; priority++) {
        // First process with this priority
        Process p1;
        p1.ID = "P" + to_string(processes.size() + 1);
        p1.arrivalTime = rand() % 3;
        p1.priority = priority;
        p1.burstTime = rand() % 5 + 1;
        processes.push_back(p1);

        // Second process with same priority (if not exceeding n)
        if (processes.size() < n) {
            Process p2;
            p2.ID = "P" + to_string(processes.size() + 1);
            p2.arrivalTime = p1.arrivalTime + rand() % 2;  // Close arrival
            p2.priority = priority;
            p2.burstTime = rand() % 5 + 1;
            processes.push_back(p2);
        }
    }

    // Fill remaining slots with random priorities (if n > 6)
    while (processes.size() < n) {
        Process p;
        p.ID = "P" + to_string(processes.size() + 1);
        p.arrivalTime = rand() % 6;
        p.priority = rand() % 3 + 1;
        p.burstTime = rand() % 5 + 1;
        processes.push_back(p);
    }

    // Sort by arrival time for realism
    sort(processes.begin(), processes.end(),
        [](const Process& a, const Process& b) {
        return a.arrivalTime < b.arrivalTime;
    });
      return processes;
}
void PrintProcesses(vector<Process> processes) {
    cout << "P\tAr\tPr\tBu\n";
    for (const auto& p : processes) {
        cout << p.ID << "\t" << p.arrivalTime << "\t"
             << p.priority << "\t" << p.burstTime << "\n";
    }
}


    vector<Process> processesTest = {
        {"P3", 6, 3,4},
        {"P4", 8, 3,5},
            {"p1"}
    };
    auto unittestresolveRR= processesTest;

#endif //SCHEDULERSERVICES_H
