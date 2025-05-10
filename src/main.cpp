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

vector<pair<string, int>> schedulePriorityRR() {
    return {};
}
double AvgWaitTime() {
    // Shaboury&Reem -> Implement here
    return {};
}
double AvgTurnaroundTime() {
    // Shaboury&Reem -> Implement here
    return{};
}
double AvgResponseTime() {
    // Shaboury&Reem -> Implement here
    return{};
}
string GanttChart(const vector<pair<string, int>>& schedule) {
    // Omar_salah -> Implement here
    return "";
}
void GUI() {
    // Shaboury&Reem -> Implement here
}

int main() {

    schedulePriorityRR();
    cout << "Welcome to the OS_Project ^_^" << endl ;
}
