#include <iostream>
#include <vector>

using namespace std;

struct Process {
    string pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time;
    int turnaround_time;
    int wait_time;
};

int main() {

    vector<Process> processes = {
        {"P1", 0, 5, 5, 0, 0, 0},
        {"P2", 1, 4, 4, 0, 0, 0},
        {"P3", 2, 2, 2, 0, 0, 0}
    };

    int current_time = 0;
    int completed = 0;

    int n = processes.size();

    while (completed < n) {

        int index = -1;

        for (int i = 0; i < n; i++) {

            if (processes[i].arrival_time <= current_time &&
                processes[i].remaining_time > 0) {

                if (index == -1 ||
                    processes[i].remaining_time <
                    processes[index].remaining_time) {

                    index = i;
                }
            }
        }

        if (index == -1) {

            current_time++;
            continue;
        }

        processes[index].remaining_time--;

        current_time++;

        if (processes[index].remaining_time == 0) {

            processes[index].completion_time =
                current_time;

            processes[index].turnaround_time =
                current_time -
                processes[index].arrival_time;

            processes[index].wait_time =
                processes[index].turnaround_time -
                processes[index].burst_time;

            completed++;
        }
    }

    cout << "PID\tCompletion\tWaiting Time\n";

    for (auto p : processes) {

        cout << p.pid << "\t"
             << p.completion_time << "\t\t"
             << p.wait_time << endl;
    }

    return 0;
}
