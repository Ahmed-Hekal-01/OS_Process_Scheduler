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

#  Core Functions

- **ProcessGeneration()**
    - *Number of processes (default=5)*
    - *Arrival time: 0-5 units (clustered early)*
    - *Priority: 1-3 (1=highest)*
    - *Burst time: 1-5 units*
    - *there is no more two Process have the same priority*
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
    - *Executes NON-Primitive priority scheduling with RR for same-priority processes*
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
    - *Resolves NoN-primitive scheduling between two same-priority processes using RR* 
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
  P	Ar	Pr	Bu
  P5	1	3	2
  P1	2	1	2
  P3	2	2	5
  P4	2	2	1
  P2	3	1	3
  Gantt Chart:
  |  P5  |  P1  |  P2  | P2 |  P3  | P4 |  P3  | P3 |
  1      3      5      7    8      10   11     13   14

  Average Waiting Time: 3.6
  Average Turnaround Time: 6.2
  Average Response Time: 3.4
  ````
##  Scheduling Metrics

| Metric              | Formula                                |
|---------------------|----------------------------------------|
| **Wait Time**       | `FinishTime - ArrivalTime - BurstTime` |
| **Turnaround Time** | `FinishTime - ArrivalTime`             |
| **Response Time**   | `FirstExecutionStart - ArrivalTime`    |

 
 