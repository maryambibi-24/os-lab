#include <iostream>
#include <vector>

using namespace std;

struct Process {
    string pid;
    int priority;
    int burst_time;
    int arrival_time;
    int remaining_time;
    int completion_time;
    int wait_time;
};

int main() {

    vector<Process> processes = {
        {"P1", 2, 4, 0, 4, 0, 0},
        {"P2", 1, 3, 1, 3, 0, 0},
        {"P3", 3, 2, 2, 2, 0, 0}
    };

    int current_time = 0;
    int completed = 0;

    while (completed < processes.size()) {

        int index = -1;

        for (int i = 0;
             i < processes.size();
             i++) {

            if (processes[i].arrival_time <= current_time &&
                processes[i].remaining_time > 0) {

                if (index == -1 ||
                    processes[i].priority <
                    processes[index].priority) {

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

            processes[index].wait_time =
                (processes[index].completion_time -
                 processes[index].arrival_time) -
                 processes[index].burst_time;

            completed++;
        }
    }

    cout << "PID\tPriority\tBurst\tArrival\tWaiting Time\n";

    for (auto p : processes) {

        cout << p.pid << "\t"
             << p.priority << "\t\t"
             << p.burst_time << "\t"
             << p.arrival_time << "\t"
             << p.wait_time << endl;
    }

    return 0;
}
