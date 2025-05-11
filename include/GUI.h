//
// Created by hekal on 5/11/25.
//

#ifndef GUI_H
#define GUI_H
#include"ProcessServices.h"
#include"MetricsServices.h"
#include "schedulerServices.h"
string GanttChart(const vector<pair<string, int>>& schedule , int FirstArrivalTime = 0 ) {
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
        string color = (colors.count(process)) ? colors[process] : "";
        string reset = "";

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
    vector<Process> Processes = GenerateProcesses();
    PrintProcesses(Processes);
    vector<pair<string, int>> schedulled = schedulePriorityRR(Processes);
    int FirstArrivalTime =Processes[0].arrivalTime;
    cout << GanttChart(schedulled , FirstArrivalTime) << endl;
    cout << "Average Waiting Time: " << AvgWaitTime(Processes , schedulled) << endl;
    cout << "Average Turnaround Time: " << AvgTurnaroundTime(Processes , schedulled) << endl;
    cout << "Average Response Time: " << AvgResponseTime(Processes , schedulled) << endl;
}
#endif //GUI_H
