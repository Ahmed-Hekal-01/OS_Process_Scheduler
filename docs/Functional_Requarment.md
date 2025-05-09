# OS Process Scheduler
*Priority Scheduling with Round-Robin Tiebreaker*

##  Data Structures

### `Process` Object
```cpp
struct Process {
    string ID;         // Format: "P1", "P2", etc.
    int arrivalTime;   // Range: 0-5 units
    int priority;      // 1 (Highest) - 3 (Lowest)
    int burstTime;     // Range: 1-5 units
};
```
### Containers 
```cpp
vector<Process> processes;           // All processes
vector<pair<string, int>> ganttChart;  // {ProcessID, EndTime}
```
#  Core Functions

- **ProcessGeneration()**
    - *Number of processes (default=5)*
    - *Arrival time: 0-5 units (clustered early)*
    - *Priority: 1-3 (1=highest)*
    - *Burst time: 1-5 units*
- **printProcesses()**
    - *Print all processes information*
    ````
  Example :
    P	Ar	Pr	Bu
    P1	1	1	5
    P2	2	2	2
    P3	4	2	2
    P4	4	2	4
    P5	5	3	2
    ````
- **PrioritySchedulerRR()**
    - *Executes priority scheduling with RR for same-priority processes*
    - *Return vector<pair<string, int>> Gantt chart entries {ProcessID, EndTime}*
    ````
    Input :
    P1 {arrival=0, priority=1, burst=3}  (Highest priority)
    P2 {arrival=1, priority=3, burst=4}  (Lowest priority)
    P3 {arrival=2, priority=1, burst=2}  (Highest priority, ties with P1)
    P4 {arrival=3, priority=2, burst=3}  (Medium priority)
    
  Output :
  [ ("P1",2), ("P3",4), ("P1",5), ("P4",8), ("P2",12) ]
    ````
- **RRScheduler()**
    - *Resolves scheduling between two same-priority processes using RR* 
    - *TimeQuantum RR time slice (default=2 units)*
    ````
    Example : 
    Input: P1{burst=3}, P2{burst=4}, quantum=2
    Output: [("P1",2), ("P2",4), ("P1",5), ("P2",7)]
    ````
- **calculateAvgWaitTime()**
    - *Return double Average wait time across all processes*
- **calculateAvgResponseTime()**
    - *Return double Average first response across all processes*
- **calculateAvgTurnaroundTime()**
    - *Return double Average completion time across all processes*
- **Gantt Chart Generator()**
    - *Input schedule Output from schedulePriorityRR()*
    - *Return string ASCII/HTML chart (implement as needed)*
    ````
    Example :
  | P1 | P2 | P3 | P1 | P2 |
  0    2    5    8    10   12
  ````

- **GUI()**
- *Print the output of the project*
  ````
  🖥️ Sample Output :
  --- Simulation Complete ---
  Gantt Chart:
  | P1 | P2 | P3 | P1 | P2 |
  0    2    5    8    10   12
  Average Waiting Time: 2.66
  Average Turnaround Time: 5.66
  Average Response Time : 3.12
  ````
##  Scheduling Metrics

| Metric              | Formula                                |
|---------------------|----------------------------------------|
| **Wait Time**       | `FinishTime - ArrivalTime - BurstTime` |
| **Turnaround Time** | `FinishTime - ArrivalTime`             |
| **Response Time**   | `FirstExecutionStart - ArrivalTime`    |

 
 