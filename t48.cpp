#include <iostream>
#include <queue>
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
        {"P1", 0, 3, 3, 0, 0, 0},
        {"P2", 0, 2, 2, 0, 0, 0},
        {"P3", 0, 4, 4, 0, 0, 0}
    };

    int quantum = 2;

    queue<int> ready_queue;

    int current_time = 0;
    int completed = 0;

    for (int i = 0;
         i < processes.size();
         i++) {

        if (processes[i].arrival_time == 0)
            ready_queue.push(i);
    }

    while (!ready_queue.empty()) {

        int index = ready_queue.front();

        ready_queue.pop();

        int slice =
            min(
                quantum,
                processes[index].remaining_time
            );

        processes[index].remaining_time -= slice;

        current_time += slice;

        if (processes[index].remaining_time > 0) {

            ready_queue.push(index);

        } else {

            processes[index].completion_time =
                current_time;

            processes[index].turnaround_time =
                processes[index].completion_time -
                processes[index].arrival_time;

            processes[index].wait_time =
                processes[index].turnaround_time -
                processes[index].burst_time;

            completed++;
        }
    }

    cout << "Quantum = "
         << quantum << endl;

    cout << "PID\tTurnaround\tWait\n";

    for (auto p : processes) {

        cout << p.pid << "\t"
             << p.turnaround_time << "\t\t"
             << p.wait_time << endl;
    }

    return 0;
}
