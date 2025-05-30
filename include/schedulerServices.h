//
// Created by hekal on 5/10/25.
//
#ifndef SCHEDULERSERVICES_H
#define SCHEDULERSERVICES_H
#include"ProcessServices.h"
using namespace std;

inline vector<pair<string, int>> resolveRR(const Process &p1, const Process &p2,  int lastTimeStamp, const int timeQuantum = 2) {
    vector<pair<string, int>> result;
    int remainingP1 = p1.burstTime;
    int remainingP2 = p2.burstTime;

    while (remainingP1 > 0 || remainingP2 > 0) {
        if (remainingP1 > 0) {
            int const execTime = min(timeQuantum, remainingP1);
            result.emplace_back(p1.ID, lastTimeStamp + execTime);
            lastTimeStamp += execTime;
            remainingP1 -= execTime;
        }
        if (remainingP2 > 0) {
            int const execTime = min(timeQuantum, remainingP2);
            result.emplace_back(p2.ID, lastTimeStamp + execTime);
            lastTimeStamp += execTime;
            remainingP2 -= execTime;
        }
    }

    return result;
}


inline vector<pair<string, int>> schedulePriorityRR(vector<Process> processes) {
    vector<pair<string, int>> ganttChart;
    int currentTime = 0;
    int const n = static_cast<int>(processes.size());
    vector done(n, false);
    int finished = 0;
    while (finished < n) {
        vector<int> readyIndices;
        for (int i = 0; i < n; ++i) {
            if (!done[i] && processes[i].arrivalTime <= currentTime)
                readyIndices.push_back(i);
        }

        if (readyIndices.empty()) {
            currentTime++;
            continue;
        }

        ranges::sort(readyIndices, [&](const int a, const int b) {
            if (processes[a].priority == processes[b].priority)
                return processes[a].arrivalTime < processes[b].arrivalTime;
            return processes[a].priority < processes[b].priority;
        });

        const int prio = processes[readyIndices[0]].priority;
        vector<int> samePrio;
        for (int i : readyIndices)
            if (processes[i].priority == prio)
                samePrio.push_back(i);

        if (samePrio.size() >= 2) {
            auto rr = resolveRR(processes[samePrio[0]], processes[samePrio[1]], currentTime);
            for (auto& p : rr) ganttChart.push_back(p);
            currentTime = rr.back().second;
            done[samePrio[0]] = true;
            done[samePrio[1]] = true;
            finished += 2;
        } else {
            int const idx = samePrio[0];
            Process& p = processes[idx];
            if (currentTime < p.arrivalTime)
                currentTime = p.arrivalTime;

            currentTime += p.burstTime;
            ganttChart.emplace_back(p.ID, currentTime);
            done[idx] = true;
            finished++;
        }
    }

    return ganttChart;
}


#endif //SCHEDULERSERVICES_H
