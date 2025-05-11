#include <climits>
#include <unistd.h>

#include "schedulerServices.h"
vector<pair<string, int>> resolveRR(const Process &p1, const Process &p2, int lastTimeStamp, int timeQuantum = 2) {
    // Emad -> Implement here "DONE"
    vector<pair<string, int>> result;

    int remainingP1 = p1.burstTime;
    int remainingP2 = p2.burstTime;

    while (remainingP1 > 0 || remainingP2 > 0) {
        if (remainingP1 > 0) {
            int execTime = min(timeQuantum, remainingP1);
            result.push_back({p1.ID, lastTimeStamp + execTime});
            lastTimeStamp += execTime;
            remainingP1 -= execTime;
        }
        if (remainingP2 > 0) {
            int execTime = min(timeQuantum, remainingP2);
            result.push_back({p2.ID, lastTimeStamp + execTime});
            lastTimeStamp += execTime;
            remainingP2 -= execTime;
        }
    }

    return result;
}


vector<pair<string, int>> schedulePriorityRR(vector<Process> processes) {
    vector<pair<string, int>> ganttChart;
    int currentTime = 0;
    int n = processes.size();
    vector<bool> done(n, false);
    int finished = 0;

    while (finished < n) {
        // Collect ready processes
        vector<int> readyIndices;
        for (int i = 0; i < n; ++i) {
            if (!done[i] && processes[i].arrivalTime <= currentTime)
                readyIndices.push_back(i);
        }

        if (readyIndices.empty()) {
            currentTime++; // No process ready
            continue;
        }

        // Sort ready processes by priority then arrivalTime
        sort(readyIndices.begin(), readyIndices.end(), [&](int a, int b) {
            if (processes[a].priority == processes[b].priority)
                return processes[a].arrivalTime < processes[b].arrivalTime;
            return processes[a].priority < processes[b].priority;
        });

        int prio = processes[readyIndices[0]].priority;

        // Collect all processes with same priority and ready
        vector<int> samePrio;
        for (int i : readyIndices)
            if (processes[i].priority == prio)
                samePrio.push_back(i);

        if (samePrio.size() >= 2) {
            // Use resolveRR on first 2
            auto rr = resolveRR(processes[samePrio[0]], processes[samePrio[1]], currentTime);
            for (auto& p : rr) ganttChart.push_back(p);
            currentTime = rr.back().second;
            done[samePrio[0]] = true;
            done[samePrio[1]] = true;
            finished += 2;
        } else {
            // Run the one process non-preemptively
            int idx = samePrio[0];
            Process& p = processes[idx];
            if (currentTime < p.arrivalTime)
                currentTime = p.arrivalTime;

            currentTime += p.burstTime;
            ganttChart.push_back({p.ID, currentTime});
            done[idx] = true;
            finished++;
        }
    }

    return ganttChart;
}
vector<Process> globalProcesses;
vector<pair<string, int>> globalSchedule;
double AvgWaitTime() {
    map<string, int> lastExecution;
    map<string, int> executedCount;

    for (auto& [id, time] : globalSchedule) {
        lastExecution[id] = time;
        executedCount[id]++;
    }

    map<string, int> waitTime;
    for (auto& p : globalProcesses) {
        int turnaround = lastExecution[p.ID] - p.arrivalTime;
        waitTime[p.ID] = turnaround - p.burstTime;
    }

    double total = 0;
    for (auto& [_, wait] : waitTime)
        total += wait;

    return total / globalProcesses.size();
}

double AvgTurnaroundTime() {
    map<string, int> lastExecution;

    for (auto& [id, time] : globalSchedule)
        lastExecution[id] = time;

    double total = 0;
    for (auto& p : globalProcesses) {
        int turnaround = lastExecution[p.ID] - p.arrivalTime;
        total += turnaround;
    }

    return total / globalProcesses.size();
}

double AvgResponseTime() {
    map<string, int> firstExecution;

    for (auto& [id, time] : globalSchedule)
        if (!firstExecution.count(id))
            firstExecution[id] = time;

    double total = 0;
    for (auto& p : globalProcesses) {
        total += firstExecution[p.ID] - p.arrivalTime;
    }

    return total / globalProcesses.size();
}

string GanttChart(const vector<pair<string, int>>& schedule ,bool enableColors, int FirstArrivalTime = 0 ) {
    if (schedule.empty()) return "No processes scheduled\n";

    map<string, string> colors = {
        {"P1", "\033[31m"},  // Red
        {"P2", "\033[32m"},  // Green
        {"P3", "\033[34m"},  // Blue
        {"P4", "\033[35m"},  // Magenta
        {"P5", "\033[33m"}   // Yellow
    };
    const string RESET = "\033[0m";

    string chart = "Gantt Chart:\n";
    string timeline = "";
    string positions = "";

    // Start from first time (i.e., first process's start time)
    int startTime = (schedule.empty() ? 0 :FirstArrivalTime);
    int prevTime = startTime;

    for (const auto& [process, endTime] : schedule) {
        int duration = endTime - prevTime;
        string color = (enableColors && colors.count(process)) ? colors[process] : "";
        string reset = enableColors ? RESET : "";


        // Chart line (with process name centered)
        string space = string(duration, ' ');
        chart += "|" + color + space + process + space + RESET;

        // Timeline markers aligned under '|'
        string timeStr = to_string(prevTime);
        timeline += "|" + string(duration * 2 + process.length(), ' ');
        positions += timeStr + string(timeline.length() - positions.length() - timeStr.length(), ' ');

        prevTime = endTime;
    }

    // Add final ending time under last bar
    string endStr = to_string(prevTime);
    timeline += "|";
    positions += endStr;

    return chart + "|\n" + positions + "\n";
}

void GUI() {
    // Shaboury&Reem -> Implement here
}
bool supportsANSIColors() {
#ifdef _WIN32
    return false; // disable on Windows
#else
    return  true;  // enable on Unix
#endif
}

int main() {
    bool enableColors = supportsANSIColors();
    vector<Process> processes = GenerateProcesses();
    PrintProcesses(processes);
    vector<pair<string, int>> Schedulled = schedulePriorityRR(processes);
    globalProcesses = processes;
    globalSchedule = Schedulled;
    int FirstArrivalTime = processes[0].arrivalTime;
    cout << GanttChart(Schedulled , enableColors,  FirstArrivalTime) << endl;
    cout << "Average Waiting Time: " << AvgWaitTime() << endl;
    cout << "Average Turnaround Time: " << AvgTurnaroundTime() << endl;
    cout << "Average Response Time: " << AvgResponseTime() << endl;

}
