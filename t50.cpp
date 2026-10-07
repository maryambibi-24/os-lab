#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

struct Process {
    string pid;
    int remaining;
};

int main() {

    queue<Process> Q1;
    queue<Process> Q2;
    queue<Process> Q3;

    // Q1: Quantum = 2
    // Q2: Quantum = 4
    // Q3: FCFS

    Q1.push({"P1", 7});
    Q1.push({"P2", 1});

    int current_time = 0;

    while (!Q1.empty() ||
           !Q2.empty() ||
           !Q3.empty()) {

        if (!Q1.empty()) {

            Process p = Q1.front();
            Q1.pop();

            int run =
                min(2, p.remaining);

            cout << "Time "
                 << current_time
                 << ": "
                 << p.pid
                 << " runs in Q1 for "
                 << run << " ms" << endl;

            p.remaining -= run;

            current_time += run;

            if (p.remaining > 0) {

                cout << p.pid
                     << " demoted to Q2"
                     << endl;

                Q2.push(p);
            }

            else {

                cout << p.pid
                     << " terminated"
                     << endl;
            }
        }

        else if (!Q2.empty()) {

            Process p = Q2.front();
            Q2.pop();

            int run =
                min(4, p.remaining);

            cout << "Time "
                 << current_time
                 << ": "
                 << p.pid
                 << " runs in Q2 for "
                 << run << " ms"
                 << endl;

            p.remaining -= run;

            current_time += run;

            if (p.remaining > 0) {

                cout << p.pid
                     << " demoted to Q3"
                     << endl;

                Q3.push(p);
            }

            else {

                cout << p.pid
                     << " terminated"
                     << endl;
            }
        }

        else if (!Q3.empty()) {

            Process p = Q3.front();
            Q3.pop();

            cout << "Time "
                 << current_time
                 << ": "
                 << p.pid
                 << " runs until finished"
                 << endl;

            current_time += p.remaining;

            p.remaining = 0;

            cout << p.pid
                 << " terminated"
                 << endl;
        }
    }

    cout << "All jobs completed." << endl;

    return 0;
}
