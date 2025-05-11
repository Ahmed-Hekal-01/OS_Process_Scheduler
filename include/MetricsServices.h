//
// Created by hekal on 5/11/25.
//
#ifndef METRICSSERVICE_H
#define METRICSSERVICE_H

inline double AvgWaitTime(const vector<Process>& Processes , const vector<pair<string, int>>& Schedule) {
    map<string, int> lastExecution;
    map<string, int> executedCount;

    for (auto& [id, time] : Schedule) {
        lastExecution[id] = time;
        executedCount[id]++;
    }

    map<string, int> waitTime;
    for (auto& p : Processes) {
        int const turnaround = lastExecution[p.ID] - p.arrivalTime;
        waitTime[p.ID] = turnaround - p.burstTime;
    }

    double total = 0;
    for (const auto &wait: waitTime | views::values)
        total += wait;

   return total / static_cast<double>(Processes.size());
}

inline double AvgTurnaroundTime(const vector<Process>& Processes , const vector<pair<string, int>>& Schedule) {
    map<string, int> lastExecution;

    for (auto& [id, time] : Schedule)
        lastExecution[id] = time;

    double total = 0;
    for (auto& p : Processes) {
        const int turnaround = lastExecution[p.ID] - p.arrivalTime;
        total += turnaround;
    }

    return total / static_cast<double>(Processes.size());
}

inline double AvgResponseTime(vector<Process> Processes, vector<pair<string, int>> Schedule) {
    map<string, int> firstStartTime;  // Maps PID to first start time
    map<string, int> lastEndTime;     // Tracks last end time for each process
    int currentTime = 0;              // System time tracker
    for (auto& [id, endTime] : Schedule) {
        // Calculate duration of this execution segment
        // If this is the first time we see this process
        if (!firstStartTime.contains(id)) {
            // Find the process to get its arrival time
            const auto proc = ranges::find_if(Processes,
                                        [&id](const Process& p) { return p.ID == id; });
            // Start time is max of arrival time or current system time
            firstStartTime[id] = max(proc->arrivalTime, currentTime);
        }
        // Update system time to the end of this segment
        currentTime = endTime;
        lastEndTime[id] = endTime;
    }
    double total = 0;
    for (auto& p : Processes) {
        if (firstStartTime.contains(p.ID)) {
            total += firstStartTime[p.ID] - p.arrivalTime;
        }
    }

    return Processes.empty() ? 0.0 : total / static_cast<double>(Processes.size());
}

#endif
