#include <iostream>
#include <vector>
#include <climits>
using namespace std;

struct Process {
    int id;
    int arrival;
    int burst;
    int remaining;
    int start = -1;
    int finish;
    int waiting;
    int turnaround;
    int response;
};

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;
    vector<Process> p(n);

    for (int i = 0; i < n; i++) {
        p[i].id = i;
        cout << "Enter Arrival Time and Burst Time for Process " << i << ": ";
        cin >> p[i].arrival >> p[i].burst;
        p[i].remaining = p[i].burst;
    }

    int completed = 0, current_time = 0;
    int total_wt = 0, total_tat = 0;

    while (completed != n) {
        int idx = -1;
        int min_remaining = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= current_time && p[i].remaining > 0) {
                if (p[i].remaining < min_remaining) {
                    min_remaining = p[i].remaining;
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            current_time++;
            continue;
        }

        // Lần đầu chạy
        if (p[idx].start == -1) p[idx].start = current_time;

        p[idx].remaining--;
        current_time++;

        if (p[idx].remaining == 0) {
            p[idx].finish = current_time;
            p[idx].turnaround = p[idx].finish - p[idx].arrival;
            p[idx].waiting = p[idx].turnaround - p[idx].burst;
            p[idx].response = p[idx].start - p[idx].arrival;

            total_wt += p[idx].waiting;
            total_tat += p[idx].turnaround;
            completed++;
        }
    }

    cout << "PName\tArrival\tBurst\tStart\tFinish\tTAT\tWT\tResponse\n";
    for (int i = 0; i < n; i++) {
        cout << p[i].id << "\t" << p[i].arrival << "\t" << p[i].burst << "\t"
             << p[i].start << "\t" << p[i].finish << "\t"
             << p[i].turnaround << "\t" << p[i].waiting << "\t"
             << p[i].response << "\n";
    }

    cout << "Average Waiting Time = " << (float)total_wt / n << "\n";
    cout << "Average Turnaround Time = " << (float)total_tat / n << "\n";

    return 0;
}

