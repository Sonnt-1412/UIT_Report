#include <iostream>
#include <vector>
#include <queue>
#include <string>
using namespace std;

struct Process {
    string name;
    int burst;
    int remaining;
    int finish;
    int waiting;
    int turnaround;
};

struct Gantt {
    string name;
    int start;
    int stop;
};

int main() {
    int n, quantum;
    cout << "Enter number of processes: ";
    cin >> n;
    cout << "Enter quantum time: ";
    cin >> quantum;

    vector<Process> p(n);
    for (int i = 0; i < n; i++) {
        cout << "Enter process name and burst time for process " << i+1 << ": ";
        cin >> p[i].name >> p[i].burst;
        p[i].remaining = p[i].burst;
        p[i].finish = 0;
    }

    queue<int> q;
    vector<Gantt> gantt;
    int time = 0;

    // Ban đầu thêm tất cả process vào queue (arrival = 0)
    for (int i = 0; i < n; i++)
        q.push(i);

    while (!q.empty()) {
        int idx = q.front();
        q.pop();

        int start_time = time;
        int run_time = (p[idx].remaining < quantum) ? p[idx].remaining : quantum;
        p[idx].remaining -= run_time;
        time += run_time;
        int stop_time = time;

        gantt.push_back({p[idx].name, start_time, stop_time});

        if (p[idx].remaining > 0)
            q.push(idx);
        else
            p[idx].finish = stop_time;
    }

    // Tính waiting time và turnaround time
    float total_wt = 0, total_tat = 0;
    for (int i = 0; i < n; i++) {
        p[i].turnaround = p[i].finish;
        p[i].waiting = p[i].turnaround - p[i].burst;
        total_wt += p[i].waiting;
        total_tat += p[i].turnaround;
    }

    // In Gantt chart
    cout << "\nGantt Chart:\n";
    cout << "Process\tStart\tStop\n";
    for (auto g : gantt)
        cout << g.name << "\t" << g.start << "\t" << g.stop << "\n";

    cout << "\nAverage Waiting Time = " << total_wt / n << "\n";
    cout << "Average Turnaround Time = " << total_tat / n << "\n";

    return 0;
}

