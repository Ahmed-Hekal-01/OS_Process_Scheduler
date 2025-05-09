#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

struct Process {
    string ID;
    int arrivalTime;
    int priority;
    int burstTime;
    int time_remaining;
};
vector<Process> processes;
void GenerateProcesses(int n = 5) {
    int arrivalTime = 0;
    srand(time(0));

    for (int i = 1; i <= n; ++i) {
        Process p;
        p.ID = "P" + to_string(i);
        if (arrivalTime < 5) {
            arrivalTime += rand() % 3;
            if (arrivalTime > 5) arrivalTime = 5;
        }

        p.arrivalTime = arrivalTime;
        p.priority = rand() % 3 + 1;
        p.burstTime = rand() % 5 + 1;

        processes.push_back(p);
    }
}

void PrintProcesses() {
    cout << "P\tAr\tPr\tBu\n";
    for (const auto& p : processes) {
        cout << p.ID << "\t" << p.arrivalTime << "\t"
             << p.priority << "\t" << p.burstTime << "\n";
    }
}

int main() {
    cout << "Welcome to the OS_Project ^_^" << endl ;
}
