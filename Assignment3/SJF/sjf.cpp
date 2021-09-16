#include <iostream>
#include <string.h>
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

int main()
{
    int n;
    struct process p[100];
    float avg_turnaround_time;
    float avg_waiting_time;
    int total_turnaround_time = 0;
    int total_waiting_time = 0;
    int is_completed[100];
    memset(is_completed, 0, sizeof(is_completed));

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

    int current_time = 0;
    int completed = 0;

    while (completed != n)
    {
        int cp = -1;
        int min = 10000000;
        for (int i = 0; i < n; i++)
        {
            if (p[i].arrival_time <= current_time && is_completed[i] == 0)
            {
                if (p[i].burst_time < min)
                {
                    min = p[i].burst_time;
                    cp = i;
                }
                if (p[i].burst_time == min)
                {
                    if (p[i].arrival_time < p[cp].arrival_time)
                    {
                        min = p[i].burst_time;
                        cp = i;
                    }
                }
            }
        }
        if (cp != -1)
        {
            p[cp].start_time = current_time;
            p[cp].completion_time = p[cp].start_time + p[cp].burst_time;
            p[cp].turnaround_time = p[cp].completion_time - p[cp].arrival_time;
            p[cp].waiting_time = p[cp].turnaround_time - p[cp].burst_time;

            total_turnaround_time += p[cp].turnaround_time;
            total_waiting_time += p[cp].waiting_time;

            is_completed[cp] = 1;
            completed++;
            current_time = p[cp].completion_time;
        }
        else
        {
            current_time++;
        }
    }

    int min_arrival_time = 10000000;
    int max_completion_time = -1;
    for (int i = 0; i < n; i++)
    {
        min_arrival_time = min(min_arrival_time, p[i].arrival_time);
        max_completion_time = max(max_completion_time, p[i].completion_time);
    }

    avg_turnaround_time = (float)total_turnaround_time / n;
    avg_waiting_time = (float)total_waiting_time / n;

    cout << endl
         << endl;

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
Variables :
AT - Arrival Time of the process
BT - Burst time of the process
ST - Start time of the process
CT - Completion time of the process
TAT - Turnaround time of the process
WT - Waiting time of the process

Formulas :
TAT = CT - AT
WT = TAT - BT
*/