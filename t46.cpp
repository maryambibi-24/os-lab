#include <iostream>
#include <vector>

using namespace std;

struct Process {
    string pid;
    int arrival_time;
    int burst_time;
    int completion_time;
    int turnaround_time;
    int wait_time;
    bool completed;
};

int main() {

    vector<Process> processes = {
        {"P1", 0, 6, 0, 0, 0, false},
        {"P2", 1, 8, 0, 0, 0, false},
        {"P3", 2, 2, 0, 0, 0, false}
    };

    int current_time = 0;
    int completed = 0;

    while (completed < processes.size()) {

        int index = -1;

        for (int i = 0;
             i < processes.size();
             i++) {

            if (!processes[i].completed &&
                processes[i].arrival_time <= current_time) {

                if (index == -1 ||
                    processes[i].burst_time <
                    processes[index].burst_time) {

                    index = i;
                }
            }
        }

        if (index == -1) {

            current_time++;
            continue;
        }

        Process &p = processes[index];

        p.completion_time =
            current_time + p.burst_time;

        p.turnaround_time =
            p.completion_time -
            p.arrival_time;

        p.wait_time =
            p.turnaround_time -
            p.burst_time;

        p.completed = true;

        current_time =
            p.completion_time;

        completed++;
    }

    cout << "PID\tBurst\tWait Time\tTurnaround Time\n";

    double total_wait = 0;

    for (auto p : processes) {

        cout << p.pid << "\t"
             << p.burst_time << "\t"
             << p.wait_time << "\t\t"
             << p.turnaround_time << endl;

        total_wait += p.wait_time;
    }

    cout << "Average Waiting Time: "
         << total_wait / processes.size()
         << " ms" << endl;

    return 0;
}
