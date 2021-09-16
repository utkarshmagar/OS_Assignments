#include <iostream>
#include <stdio.h>
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
    int burst_remaining[100];
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
        burst_remaining[i] = p[i].burst_time;
    }

    int current_time = 0;
    int completed = 0;
    int gantt_chart[100];
    int count = 0;

    while (completed != n)
    {
        int cp = -1;
        int min = 10000000;

        for (int i = 0; i < n; i++)
        {
            if (p[i].arrival_time <= current_time && is_completed[i] == 0)
            // Finding Process with minimum Burst Time from ready queue
            {
                if (burst_remaining[i] < min)
                {
                    min = burst_remaining[i];
                    cp = i;
                }
                if (burst_remaining[i] == min)
                // Using FCFS if Burst Time is same
                {
                    if (p[i].arrival_time < p[cp].arrival_time)
                    {
                        min = burst_remaining[i];
                        cp = i;
                    }
                }
            }
        }

        if (cp != -1)
        //Process Found
        {
            if (burst_remaining[cp] == p[cp].burst_time)
            //Process Getting CPU for the first time
            {
                p[cp].start_time = current_time;
            }
            burst_remaining[cp] -= 1;
            current_time++;

            if (burst_remaining[cp] == 0)
            //Process Completed
            {
                p[cp].completion_time = current_time;
                p[cp].turnaround_time = p[cp].completion_time - p[cp].arrival_time;
                p[cp].waiting_time = p[cp].turnaround_time - p[cp].burst_time;

                total_turnaround_time += p[cp].turnaround_time;
                total_waiting_time += p[cp].waiting_time;

                is_completed[cp] = 1;
                //Marking Process as Completed
                completed++;
            }
            gantt_chart[count] = p[cp].pid;
            count++;
        }
        else
        {
            current_time++;
        }
    }

    avg_turnaround_time = (float)total_turnaround_time / n;
    avg_waiting_time = (float)total_waiting_time / n;

    cout << endl
         << "GANTT CHART :-" << endl;

    int count1 = 0;
    cout << "| "
         << "P" << gantt_chart[count1];
    while (count1 != count - 1)
    {
        if (gantt_chart[count1] != gantt_chart[count1 + 1])
        {
            cout << " | "
                 << "P" << gantt_chart[count1 + 1];
        }
        count1++;
    }
    cout << " | " << endl;

    count1 = 0;
    int timer = 0;
    cout << timer;
    while (count1 != count)
    {
        if (gantt_chart[count1] != gantt_chart[count1 + 1])
        {
            if (timer < 10 & timer + 1 < 10)
            {
                cout << "    " << timer + 1;
            }
            else if (timer > 10 & timer + 1 > 10)
            {
                cout << "   " << timer + 1;
            }
            else
            {
                cout << "    " << timer + 1;
            }
        }
        count1++;
        timer++;
    }

    cout << endl
         << endl;

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