//
// Created by hekal on 5/11/25.
//

#ifndef GUI_H
#define GUI_H
#include"ProcessServices.h"
#include"MetricsServices.h"
#include "schedulerServices.h"

inline string GanttChart(const vector<pair<string, int>>& schedule , const int FirstArrivalTime = 0 ) {
    if (schedule.empty()) return "No processes scheduled\n";

    map<string, string> colors = {
        {"P1", "\033[31m"},
        {"P2", "\033[32m"},
        {"P3", "\033[34m"},
        {"P4", "\033[35m"},
        {"P5", "\033[33m"}
    };
    const string RESET = "\033[0m";

    string chart = "Gantt Chart:\n";
    string timeline , positions;

    int const  startTime = (schedule.empty() ? 0 :FirstArrivalTime);
    int prevTime = startTime;

    for (const auto& [process, endTime] : schedule) {
        int const duration = endTime - prevTime;
        string color = (colors.count(process)) ? colors[process] : "";
        string reset ;
        auto space = string(duration, ' ');
        chart.append("|").append(color).append(space).append(process).append(space).append(RESET);
        string timeStr = to_string(prevTime);
        timeline += "|" + string(duration * 2 + process.length(), ' ');
        positions += timeStr + string(timeline.length() - positions.length() - timeStr.length(), ' ');

        prevTime = endTime;
    }

    string const endStr = to_string(prevTime);
    positions += endStr;
    return chart + "|\n" + positions + "\n";
}

inline void GUI() {
    const vector<Process> Processes = GenerateProcesses();
    PrintProcesses(Processes);
    const vector<pair<string, int>> schedule = schedulePriorityRR(Processes);
    const int FirstArrivalTime =Processes[0].arrivalTime;
    cout << GanttChart(schedule , FirstArrivalTime) << endl;
    cout << "Average Waiting Time: " << AvgWaitTime(Processes , schedule) << endl;
    cout << "Average Turnaround Time: " << AvgTurnaroundTime(Processes , schedule) << endl;
    cout << "Average Response Time: " << AvgResponseTime(Processes , schedule) << endl;
}
#endif //GUI_H
