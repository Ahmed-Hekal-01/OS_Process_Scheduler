//
// Created by hekal on 5/11/25.
//
#ifndef METRICSSERVICE_H
#define METRICSSERVICE_H

double AvgWaitTime(vector<Process> Processes , vector<pair<string, int>> Schedule) {
    map<string, int> lastExecution;
    map<string, int> executedCount;

    for (auto& [id, time] : Schedule) {
        lastExecution[id] = time;
        executedCount[id]++;
    }

    map<string, int> waitTime;
    for (auto& p : Processes) {
        int turnaround = lastExecution[p.ID] - p.arrivalTime;
        waitTime[p.ID] = turnaround - p.burstTime;
    }

    double total = 0;
    for (auto& [_, wait] : waitTime)
        total += wait;

    return total / Processes.size();
}

double AvgTurnaroundTime(vector<Process> Processes , vector<pair<string, int>> Schedule) {
    map<string, int> lastExecution;

    for (auto& [id, time] : Schedule)
        lastExecution[id] = time;

    double total = 0;
    for (auto& p : Processes) {
        int turnaround = lastExecution[p.ID] - p.arrivalTime;
        total += turnaround;
    }

    return total / Processes.size();
}

double AvgResponseTime(vector<Process> Processes , vector<pair<string, int>> Schedule) {
    map<string, int> firstExecution;

    for (auto& [id, time] : Schedule)
        if (!firstExecution.count(id))
            firstExecution[id] = time;

    double total = 0;
    for (auto& p : Processes) {
        total += firstExecution[p.ID] - p.arrivalTime;
    }

    return total / Processes.size();
}
#endif
