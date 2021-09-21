#include <iostream>
#include <algorithm>
#include <string.h>
#include <queue>
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

bool compare1(process p1, process p2)
{
    return p1.arrival_time < p2.arrival_time;
}

bool compare2(process p1, process p2)
{
    return p1.pid < p2.pid;
}

int main()
{
    int n;
    int tq;
    struct process p[100];
    float avg_turnaround_time;
    float avg_waiting_time;
    int total_turnaround_time = 0;
    int total_waiting_time = 0;
    int burst_remaining[100];
    int cp;

    cout << "ENTER THE NO. OF PROCESSES :- ";
    cin >> n;
    cout << "ENTER TIME QUANTUM :- ";
    cin >> tq;

    for (int i = 0; i < n; i++)
    {
        cout << endl;
        cout << "ENTER ARRIVAL TIME OF PROCESS " << i + 1 << " :- ";
        cin >> p[i].arrival_time;
        cout << "ENTER BURST TIME OF PROCESS " << i + 1 << " :- ";
        cin >> p[i].burst_time;
        burst_remaining[i] = p[i].burst_time;
        p[i].pid = i + 1;
    }

    sort(p, p + n, compare1); // Sorting Process according to arrival time

    queue<int> q;
    int current_time = 0;
    q.push(0);
    int completed = 0;
    int mark[100];
    memset(mark, 0, sizeof(mark));
    mark[0] = 1;

    int gantt_chart_p[100];
    int gantt_chart_t[100];
    int count = 0;

    while (completed != n)
    {
        cp = q.front();
        q.pop();

        if (burst_remaining[cp] == p[cp].burst_time) // Process Getting CPU for First Time
        {
            p[cp].start_time = max(current_time, p[cp].arrival_time);
            current_time = p[cp].start_time;
        }

        if (burst_remaining[cp] - tq > 0) // Process Terminated in Between / Context Switching
        {
            burst_remaining[cp] -= tq;
            current_time += tq;
        }
        else //Process is Completed
        {
            current_time += burst_remaining[cp];
            burst_remaining[cp] = 0;
            completed++;

            p[cp].completion_time = current_time;
            p[cp].turnaround_time = p[cp].completion_time - p[cp].arrival_time;
            p[cp].waiting_time = p[cp].turnaround_time - p[cp].burst_time;

            total_turnaround_time += p[cp].turnaround_time;
            total_waiting_time += p[cp].waiting_time;
        }
        gantt_chart_p[count] = p[cp].pid;
        gantt_chart_t[count] = current_time;
        count++;

        for (int i = 1; i < n; i++) // Process arrived when some other process is executing
        {
            if (burst_remaining[i] > 0 && p[i].arrival_time <= current_time && mark[i] == 0)
            {
                q.push(i);
                mark[i] = 1;
            }
        }
        if (burst_remaining[cp] > 0) // If Current Process is stopped due to QT and still remaining
        {
            q.push(cp);
        }

        if (q.empty()) // If queue is empty then pick first process from the list which is incomplete
        {
            for (int i = 1; i < n; i++)
            {
                if (burst_remaining[i] > 0)
                {
                    q.push(i);
                    mark[i] = 1;
                    break;
                }
            }
        }
    }

    avg_turnaround_time = (float)total_turnaround_time / n;
    avg_waiting_time = (float)total_waiting_time / n;

    sort(p, p + n, compare2); // Sorting according to Process ID

    cout << endl
         << "GANTT CHART :-" << endl;

    int count1 = 0;
    cout << "| "
         << "P" << gantt_chart_p[count1];
    while (count1 != count - 1)
    {
        if (gantt_chart_p[count1] != gantt_chart_p[count1 + 1])
        {
            cout << " | "
                 << "P" << gantt_chart_p[count1 + 1];
        }
        count1++;
    }
    cout << " | " << endl;

    count1 = 0;
    cout << "0";
    while (count1 != count)
    {
        if (gantt_chart_p[count1] != gantt_chart_p[count1 + 1])
        {
            if (gantt_chart_t[count1] < 10 & gantt_chart_t[count1 + 1] < 10)
            {
                cout << "    " << gantt_chart_t[count1];
            }
            else if (gantt_chart_t[count1] > 10 & gantt_chart_t[count1 + 1] > 10)
            {
                cout << "   " << gantt_chart_t[count1];
            }
            else
            {
                cout << "    " << gantt_chart_t[count1];
            }
        }
        count1++;
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