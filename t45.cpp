#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Process {
    string pid;
    int arrival_time;
    int burst_time;
    int completion_time;
    int turnaround_time;
    int wait_time;
};

void schedule_fcfs(vector<Process>& processes) {

    sort(
        processes.begin(),
        processes.end(),
        [](Process a, Process b) {
            return a.arrival_time <
                   b.arrival_time;
        }
    );

    int current_time = 0;

    for (auto &p : processes) {

        if (current_time < p.arrival_time)
            current_time = p.arrival_time;

        p.completion_time =
            current_time + p.burst_time;

        p.turnaround_time =
            p.completion_time -
            p.arrival_time;

        p.wait_time =
            p.turnaround_time -
            p.burst_time;

        current_time =
            p.completion_time;
    }
}


int main() {

    vector<Process> processes = {
        {"P1", 0, 5, 0, 0, 0},
        {"P2", 1, 3, 0, 0, 0},
        {"P3", 2, 8, 0, 0, 0}
    };

    schedule_fcfs(processes);

    cout << "PID\tArrival\tBurst\tCompletion\t"
         << "Turnaround\tWait\n";

    double total_wait = 0;

    for (auto p : processes) {

        cout << p.pid << "\t"
             << p.arrival_time << "\t"
             << p.burst_time << "\t"
             << p.completion_time << "\t\t"
             << p.turnaround_time << "\t\t"
             << p.wait_time << endl;

        total_wait += p.wait_time;
    }

    cout << "Average Waiting Time: "
         << total_wait / processes.size()
         << " ms" << endl;

    return 0;
}
