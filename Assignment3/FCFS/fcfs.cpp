#include <iostream>
#include <algorithm>
using namespace std;

struct process
{
    int pid;
    int arrival_time;
    int burst_time;
    int start_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
};

bool compareArrival(process p1, process p2)
{
    return p1.arrival_time < p2.arrival_time;
}

bool compareID(process p1, process p2)
{
    return p1.pid < p2.pid;
}

int main()
{

    int n;
    struct process p[100];
    float avg_turnaround_time;
    float avg_waiting_time;
    int total_turnaround_time = 0;
    int total_waiting_time = 0;

    cout << "ENTER THE NO. OF PROCESSES :- ";
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        cout << endl;
        cout << "ENTER ARRIVAL TIME OF PROCESS " << i + 1 << " :- ";
        cin >> p[i].arrival_time;
        cout << "ENTER BURST TIME OF PROCESS " << i + 1 << " :- ";
        cin >> p[i].burst_time;
        p[i].pid = i + 1;
    }

    sort(p, p + n, compareArrival);

    for (int i = 0; i < n; i++)
    {
        p[i].start_time = (i == 0) ? p[i].arrival_time : max(p[i - 1].completion_time, p[i].arrival_time);
        p[i].completion_time = p[i].start_time + p[i].burst_time;
        p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;
        p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;

        total_turnaround_time += p[i].turnaround_time;
        total_waiting_time += p[i].waiting_time;
    }

    avg_turnaround_time = (float)total_turnaround_time / n;
    avg_waiting_time = (float)total_waiting_time / n;

    sort(p, p + n, compareID);

    cout << endl;
    cout << "P\t"
         << "AT\t"
         << "BT\t"
         << "ST\t"
         << "CT\t"
         << "TAT\t"
         << "WT\t"
         << "\n"
         << endl;

    for (int i = 0; i < n; i++)
    {
        cout << p[i].pid << "\t"
             << p[i].arrival_time << "\t"
             << p[i].burst_time << "\t"
             << p[i].start_time << "\t"
             << p[i].completion_time << "\t"
             << p[i].turnaround_time << "\t"
             << p[i].waiting_time << "\t"
             << "\n"
             << endl;
    }

    cout << "AVERAGE TURNAROUND TIME :- " << avg_turnaround_time << endl;
    cout << "AVERAGE WAITING TIME :- " << avg_waiting_time << endl;

    return 0;
}

/*
Variables :-
AT - Arrival Time of the process
BT - Burst time of the process
ST - Start time of the process
CT - Completion time of the process
TAT - Turnaround time of the process
WT - Waiting time of the process

Formulas :
TAT = CT - AT
WT = TAT - BT
RT = ST - AT
*/